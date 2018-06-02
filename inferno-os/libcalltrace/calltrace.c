/* call-trace.c - converting addresses to files and lines
   Copyright (C) 1997-2017 Free Software Foundation, Inc.
   Contributed by Emil Ohlsson <emil.ohlsson@kottland.net>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

/* Derived from addr2line by Ulrich.Lauther@mchp.siemens.de */

/**** Includes *****/

#include <bfd.h>
#include <demangle.h>
#include <errno.h>
#include <libiberty.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**** Defines ****/

#define LINEBUF 256

/** Function decorators **/

#define INSTRUMENT __attribute__((no_instrument_function))
#define INSTRUMENT_CONSTRUCTOR __attribute__((no_instrument_function, constructor))
#define INSTRUMENT_DESTRUCTOR __attribute__((no_instrument_function, destructor))

/** Arguments **/

#ifndef UNWIND_INLINES
#define UNWIND_INLINES 1
#endif

#ifndef WITH_ADDRESSES
#define WITH_ADDRESSES 1
#endif

#ifndef WITH_FUNCTIONS
#define WITH_FUNCTIONS 1
#endif

#ifndef DO_DEMANGLE
#define DO_DEMANGLE 1
#endif

#ifndef PRETTY_PRINT
#define PRETTY_PRINT 1
#endif

#ifndef BASE_NAMES
#define BASE_NAMES 1
#endif

/** Helpers **/

#define err(fmt, ...) fprintf(stderr, "ERR: " fmt "\n", ##__VA_ARGS__)
#define log(fmt, ...) fprintf(stderr, fmt "\n", ##__VA_ARGS__)

/**** Data ****/

/** Options **/

static bfd_boolean unwind_inlines = UNWIND_INLINES; /* unwind inlined functions. */
static bfd_boolean with_addresses = WITH_ADDRESSES; /* show addresses.  */
static bfd_boolean with_functions = WITH_FUNCTIONS; /* show function names.  */
static bfd_boolean do_demangle = DO_DEMANGLE;       /* demangle names.  */
static bfd_boolean pretty_print = PRETTY_PRINT;     /* print on one line.  */
static bfd_boolean base_names = BASE_NAMES;         /* strip directory names.  */

/* These global variables are used to pass information between translate_addresses and
 * find_address_in_section. */

static asymbol **syms;
static bfd *abfd;
static bfd_boolean found;
static bfd_vma pc;
static const char *filename;
static const char *functionname;
static unsigned int discriminator;
static unsigned int line;

/**** Private functions ****/

/** Preparation and cleanup **/

static void INSTRUMENT slurp(bfd *abfd)
{
    long symcount;
    unsigned int size;

    if ((bfd_get_file_flags(abfd) & HAS_SYMS) == 0) return;

    symcount = bfd_read_minisymbols(abfd, false, (void *) &syms, &size);
    if (symcount == 0) {
        symcount = bfd_read_minisymbols(abfd, TRUE, (void *) &syms, &size);
    }
    if (symcount < 0) {
        err("Could not read symbol table");
    }
}

static void INSTRUMENT_CONSTRUCTOR setup()
{
    char **matching;
    const char *self = "/proc/self/exe";

    bfd_init();

    abfd = bfd_openr(self, NULL);
    if (!abfd) {
        err("Unable to open self");
        return;
    }

    if (bfd_check_format(abfd, bfd_archive)) {
        err("Cannot identify self");
        return;
    }

    if (!bfd_check_format_matches(abfd, bfd_object, &matching)) {
        err("Format does not match");
    }

    slurp(abfd);
}

static void INSTRUMENT_DESTRUCTOR teardown()
{
    free(syms);
    bfd_close(abfd);
}

/** Translation **/

/**
 * Look for an address in a section.  This is called via bfd_map_over_sections.
 */
static void INSTRUMENT find_address_in_section(bfd *abfd, asection *section,
                                               void *data ATTRIBUTE_UNUSED)
{
    bfd_vma vma;
    bfd_size_type size;

    if (found) return;

    if ((bfd_get_section_flags(abfd, section) & SEC_ALLOC) == 0) return;

    vma = bfd_get_section_vma(abfd, section);
    if (pc < vma) return;

    size = bfd_get_section_size(section);
    if (pc >= vma + size) return;

    found = bfd_find_nearest_line_discriminator(abfd, section, syms, pc - vma, &filename,
                                                &functionname, &line, &discriminator);
}

static void INSTRUMENT describe_address(char* buffer, size_t buffer_length, void *addr)
{
    size_t buffer_index = 0;

    void INSTRUMENT bprintf(const char *fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        buffer_index += vsnprintf(buffer + buffer_index, buffer_length - buffer_index, fmt, args);
        va_end(args);
    }

    pc = (intptr_t) addr;
    if (with_addresses) {
        bprintf("%p ", addr);
    }

    found = FALSE;
    bfd_map_over_sections(abfd, find_address_in_section, NULL);

    if (!found) {
        if (with_functions) {
            if (pretty_print) {
                bprintf("?? ");
            } else {
                bprintf("??");
            }
        }
        bprintf("??:0");
    } else {
        while (1) {
            if (with_functions) {
                const char *name;
                char *alloc = NULL;

                name = functionname;
                if (name == NULL || *name == '\0') {
                    name = "??";
                } else if (do_demangle) {
                    alloc = bfd_demangle(abfd, name, DMGL_ANSI | DMGL_PARAMS);
                    if (alloc != NULL) name = alloc;
                }

                bprintf("%s", name);
                if (pretty_print) {
                    bprintf(" at ");
                }

                if (alloc != NULL) free(alloc);
            }

            if (base_names && filename != NULL) {
                char *h;

                h = strrchr(filename, '/');
                if (h != NULL) filename = h + 1;
            }

            bprintf("%s:", filename ? filename : "??");
            if (line != 0) {
                if (discriminator != 0) {
                    bprintf("%u (discriminator %u)", line, discriminator);
                }
                else {
                    bprintf("%u", line);
                }
            } else {
                bprintf("?");
            }
            if (!unwind_inlines) {
                found = FALSE;
            } else {
                found = bfd_find_inliner_info(abfd, &filename, &functionname, &line);
            }
            if (!found) break;
            if (pretty_print) {
                bprintf(" (inlined by) ");
            }
        }
    }
}

/**** Public functions ****/

void INSTRUMENT __cyg_profile_func_enter(void *this_fn, void *call_site)
{
    char from[LINEBUF] = {0};
    char to[LINEBUF] = {0};

    describe_address(to, LINEBUF, this_fn);
    describe_address(from, LINEBUF, call_site);
    log("-trace- calling [%s] from [%s]", to, from);
}

void INSTRUMENT __cyg_profile_func_exit(void *this_fn ATTRIBUTE_UNUSED,
                                        void *call_site ATTRIBUTE_UNUSED)
{
}


