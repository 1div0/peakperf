/*
 * Code based on cpufetch project at
 * https://github.com/Dr-Noob/cpufetch/blob/master/src/x86/uarch.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpufetch.hpp"
#include "cpuid.hpp"
#include "uarch.hpp"

// Data not available
#define NA                   -1

#define UARCH_START if (false) {}
#define CHECK_UARCH(arch, ef_, f_, em_, m_, s_, str, uarch, process) \
   else if (ef_ == ef && f_ == f && (em_ == NA || em_ == em) && (m_ == NA || m_ == m) && (s_ == NA || s_ == s)) fill_uarch(arch, str, uarch);
#define UARCH_END else { printf("Unknown microarchitecture detected: M=0x%.8X EM=0x%.8X F=0x%.8X EF=0x%.8X S=0x%.8X", m, em, f, ef, s); fill_uarch(arch, "Unknown", UARCH_UNKNOWN); }

void fill_uarch(struct uarch* arch, const char* str, MICROARCH u) {
  arch->uarch_str = (char*) malloc(sizeof(char) * (strlen(str)+1));
  strcpy(arch->uarch_str, str);
  arch->uarch = u;
}

struct uarch* get_uarch_from_cpuid_intel(uint32_t ef, uint32_t f, uint32_t em, uint32_t m, int s) {
  struct uarch* arch = (struct uarch*) malloc(sizeof(struct uarch));

  // NOTE: Process (last argument) is ignored, but included for compatiblity with
  // cpufetch
  //
  // EF: Extended Family                                                           //
  // F:  Family                                                                    //
  // EM: Extended Model                                                            //
  // M: Model                                                                      //
  // S: Stepping                                                                   //
  // ----------------------------------------------------------------------------- //
  //                EF  F  EM   M   S                                              //
  UARCH_START
  CHECK_UARCH(arch, 0,  5,  0,  0, NA, "P5",              UARCH_P5,              800)
  CHECK_UARCH(arch, 0,  5,  0,  1, NA, "P5",              UARCH_P5,              800)
  CHECK_UARCH(arch, 0,  5,  0,  2, NA, "P5",              UARCH_P5,              UNK)
  CHECK_UARCH(arch, 0,  5,  0,  3, NA, "P5",              UARCH_P5,              600)
  CHECK_UARCH(arch, 0,  5,  0,  4, NA, "P5 MMX",          UARCH_P5,              UNK)
  CHECK_UARCH(arch, 0,  5,  0,  7, NA, "P5 MMX",          UARCH_P5,              UNK)
  CHECK_UARCH(arch, 0,  5,  0,  8, NA, "P5 MMX",          UARCH_P5,              250)
  CHECK_UARCH(arch, 0,  5,  0,  9,  0, "Lakemont",        UARCH_LAKEMONT,         32)
  CHECK_UARCH(arch, 0,  5,  0,  9, NA, "P5 MMX",          UARCH_P5,              UNK)
  CHECK_UARCH(arch, 0,  5,  0, 10,  0, "Lakemont",        UARCH_LAKEMONT,         32)
  CHECK_UARCH(arch, 0,  6,  0,  0, NA, "P6 Pentium II",   UARCH_P6,              UNK)
  CHECK_UARCH(arch, 0,  6,  0,  1, NA, "P6 Pentium II",   UARCH_P6,              UNK) // process depends on core
  CHECK_UARCH(arch, 0,  6,  0,  2, NA, "P6 Pentium II",   UARCH_P6,              UNK)
  CHECK_UARCH(arch, 0,  6,  0,  3, NA, "P6 Pentium II",   UARCH_P6,              350)
  CHECK_UARCH(arch, 0,  6,  0,  4, NA, "P6 Pentium II",   UARCH_P6,              UNK)
  CHECK_UARCH(arch, 0,  6,  0,  5, NA, "P6 Pentium II",   UARCH_P6,              250)
  CHECK_UARCH(arch, 0,  6,  0,  6, NA, "P6 Pentium II",   UARCH_P6,              UNK)
  CHECK_UARCH(arch, 0,  6,  0,  7, NA, "P6 Pentium III",  UARCH_P6,              250)
  CHECK_UARCH(arch, 0,  6,  0,  8, NA, "P6 Pentium III",  UARCH_P6,              180)
  CHECK_UARCH(arch, 0,  6,  0,  9, NA, "P6 Pentium M",    UARCH_P6,              130)
  CHECK_UARCH(arch, 0,  6,  0, 10, NA, "P6 Pentium III",  UARCH_P6,              180)
  CHECK_UARCH(arch, 0,  6,  0, 11, NA, "P6 Pentium III",  UARCH_P6,              130)
  CHECK_UARCH(arch, 0,  6,  0, 13, NA, "Dothan",          UARCH_DOTHAN,          UNK)  // process depends on core
  CHECK_UARCH(arch, 0,  6,  0, 14, NA, "Yonah",           UARCH_YONAH,            65)
  CHECK_UARCH(arch, 0,  6,  0, 15, NA, "Merom",           UARCH_MEROM,            65)
  CHECK_UARCH(arch, 0,  6,  1,  5, NA, "Dothan",          UARCH_DOTHAN,           90)
  CHECK_UARCH(arch, 0,  6,  1,  6, NA, "Merom",           UARCH_MEROM,            65)
  CHECK_UARCH(arch, 0,  6,  1,  7, NA, "Penryn",          UARCH_PENYR,            45)
  CHECK_UARCH(arch, 0,  6,  1, 10, NA, "Nehalem",         UARCH_NEHALEM,          45)
  CHECK_UARCH(arch, 0,  6,  1, 12, NA, "Bonnell",         UARCH_BONNELL,          45)
  CHECK_UARCH(arch, 0,  6,  1, 13, NA, "Penryn",          UARCH_PENYR,            45)
  CHECK_UARCH(arch, 0,  6,  1, 14, NA, "Nehalem",         UARCH_NEHALEM,          45)
  CHECK_UARCH(arch, 0,  6,  1, 15, NA, "Nehalem",         UARCH_NEHALEM,          45)
  CHECK_UARCH(arch, 0,  6,  2,  5, NA, "Westmere",        UARCH_WESTMERE,         32)
  CHECK_UARCH(arch, 0,  6,  2 , 6, NA, "Bonnell",         UARCH_BONNELL,          45)
  CHECK_UARCH(arch, 0,  6,  2,  7, NA, "Saltwell",        UARCH_SALTWELL,         32)
  CHECK_UARCH(arch, 0,  6,  2, 10, NA, "Sandy Bridge",    UARCH_SANDY_BRIDGE,     32)
  CHECK_UARCH(arch, 0,  6,  2, 12, NA, "Westmere",        UARCH_WESTMERE,         32)
  CHECK_UARCH(arch, 0,  6,  2, 13, NA, "Sandy Bridge",    UARCH_SANDY_BRIDGE,     32)
  CHECK_UARCH(arch, 0,  6,  2, 14, NA, "Nehalem",         UARCH_NEHALEM,          45)
  CHECK_UARCH(arch, 0,  6,  2, 15, NA, "Westmere",        UARCH_WESTMERE,         32)
  CHECK_UARCH(arch, 0,  6,  3,  5, NA, "Saltwell",        UARCH_SALTWELL,         14)
  CHECK_UARCH(arch, 0,  6,  3,  6, NA, "Saltwell",        UARCH_SALTWELL,         32)
  CHECK_UARCH(arch, 0,  6,  3,  7, NA, "Silvermont",      UARCH_SILVERMONT,       22)
  CHECK_UARCH(arch, 0,  6,  3, 10, NA, "Ivy Bridge",      UARCH_IVY_BRIDGE,       22)
  CHECK_UARCH(arch, 0,  6,  3, 12, NA, "Haswell",         UARCH_HASWELL,          22)
  CHECK_UARCH(arch, 0,  6,  3, 13, NA, "Broadwell",       UARCH_BROADWELL,        14)
  CHECK_UARCH(arch, 0,  6,  3, 14, NA, "Ivy Bridge",      UARCH_IVY_BRIDGE,       22)
  CHECK_UARCH(arch, 0,  6,  3, 15, NA, "Haswell",         UARCH_HASWELL,          22)
  CHECK_UARCH(arch, 0,  6,  4,  5, NA, "Haswell",         UARCH_HASWELL,          22)
  CHECK_UARCH(arch, 0,  6,  4,  6, NA, "Haswell",         UARCH_HASWELL,          22)
  CHECK_UARCH(arch, 0,  6,  4,  7, NA, "Broadwell",       UARCH_BROADWELL,        14)
  CHECK_UARCH(arch, 0,  6,  4, 10, NA, "Silvermont",      UARCH_SILVERMONT,       22) // no docs, but /proc/cpuinfo seen in wild
  CHECK_UARCH(arch, 0,  6,  4, 12, NA, "Airmont",         UARCH_AIRMONT,          14)
  CHECK_UARCH(arch, 0,  6,  4, 13, NA, "Silvermont",      UARCH_SILVERMONT,       22)
  CHECK_UARCH(arch, 0,  6,  4, 14,  8, "Kaby Lake",       UARCH_KABY_LAKE,        14)
  CHECK_UARCH(arch, 0,  6,  4, 14, NA, "Skylake",         UARCH_SKYLAKE,          14)
  CHECK_UARCH(arch, 0,  6,  4, 15, NA, "Broadwell",       UARCH_BROADWELL,        14)
  CHECK_UARCH(arch, 0,  6,  5,  5,  6, "Cascade Lake",    UARCH_CASCADE_LAKE,     14) // no docs, but example from Greg Stewart
  CHECK_UARCH(arch, 0,  6,  5,  5,  7, "Cascade Lake",    UARCH_CASCADE_LAKE,     14)
  CHECK_UARCH(arch, 0,  6,  5,  5, 10, "Cooper Lake",     UARCH_COOPER_LAKE,      14)
  CHECK_UARCH(arch, 0,  6,  5,  5, NA, "Skylake",         UARCH_SKYLAKE,          14)
  CHECK_UARCH(arch, 0,  6,  5,  6, NA, "Broadwell",       UARCH_BROADWELL,        14)
  CHECK_UARCH(arch, 0,  6,  5,  7, NA, "Knights Landing", UARCH_KNIGHTS_LANDING,  14)
  CHECK_UARCH(arch, 0,  6,  5, 10, NA, "Silvermont",      UARCH_SILVERMONT,       22) // no spec update; only MSR_CPUID_table* so far
  CHECK_UARCH(arch, 0,  6,  5, 12, NA, "Goldmont",        UARCH_GOLDMONT,         14)
  CHECK_UARCH(arch, 0,  6,  5, 13, NA, "Silvermont",      UARCH_SILVERMONT,       22) // no spec update; only MSR_CPUID_table* so far
  CHECK_UARCH(arch, 0,  6,  5, 14,  8, "Kaby Lake",       UARCH_KABY_LAKE,        14)
  CHECK_UARCH(arch, 0,  6,  5, 14, NA, "Skylake",         UARCH_SKYLAKE,          14)
  CHECK_UARCH(arch, 0,  6,  5, 15, NA, "Goldmont",        UARCH_GOLDMONT,         14)
  CHECK_UARCH(arch, 0,  6,  6,  6, NA, "Palm Cove",       UARCH_PALM_COVE,        10) // no spec update; only MSR_CPUID_table* so far
  CHECK_UARCH(arch, 0,  6,  6, 10, NA, "Sunny Cove",      UARCH_SUNNY_COVE,       10) // no spec update; only MSR_CPUID_table* so far
  CHECK_UARCH(arch, 0,  6,  6, 12, NA, "Sunny Cove",      UARCH_SUNNY_COVE,       10) // no spec update; only MSR_CPUID_table* so far
  CHECK_UARCH(arch, 0,  6,  7,  5, NA, "Airmont",         UARCH_AIRMONT,          14) // no spec update; whispers & rumors
  CHECK_UARCH(arch, 0,  6,  7, 10, NA, "Goldmont Plus",   UARCH_GOLDMONT_PLUS,    14)
  CHECK_UARCH(arch, 0,  6,  7, 13, NA, "Sunny Cove",      UARCH_SUNNY_COVE,       10) // no spec update; only MSR_CPUID_table* so far
  CHECK_UARCH(arch, 0,  6,  7, 14, NA, "Ice Lake",        UARCH_ICE_LAKE,         10)
  CHECK_UARCH(arch, 0,  6,  8,  5, NA, "Knights Mill",    UARCH_KNIGHTS_MILL,     14) // no spec update; only MSR_CPUID_table* so far
  CHECK_UARCH(arch, 0,  6,  8,  6, NA, "Tremont",         UARCH_TREMONT,          10) // LX*
  CHECK_UARCH(arch, 0,  6,  8, 10, NA, "Tremont",         UARCH_TREMONT,          10) // no spec update; only geekbench.com example
  CHECK_UARCH(arch, 0,  6,  8, 12, NA, "Tiger Lake",      UARCH_TIGER_LAKE,       10) // instlatx64
  CHECK_UARCH(arch, 0,  6,  8, 13, NA, "Tiger Lake",      UARCH_TIGER_LAKE,       10) // instlatx64
  // CHECK_UARCH(arch, 0,  6,  8, 14,  9, ...) It is not possible to determine uarch only from CPUID dump (can be Kaby Lake or Amber Lake)
  // CHECK_UARCH(arch, 0,  6,  8, 14, 10, ...) It is not possible to determine uarch only from CPUID dump (can be Kaby Lake R or Coffee Lake U)
  CHECK_UARCH(arch, 0,  6,  8, 14, 11, "Whiskey Lake",    UARCH_WHISKEY_LAKE,     14) // wikichip
  CHECK_UARCH(arch, 0,  6,  8, 14, 12, "Comet Lake",      UARCH_COMET_LAKE,       14) // wikichip
  CHECK_UARCH(arch, 0,  6,  9,  6, NA, "Tremont",         UARCH_TREMONT,          10) // LX*
  CHECK_UARCH(arch, 0,  6,  9,  7, NA, "Alder Lake",      UARCH_ALDER_LAKE,       10) // instlatx64 (Alder Lake-S)
  CHECK_UARCH(arch, 0,  6,  9, 10, NA, "Alder Lake",      UARCH_ALDER_LAKE,       10) // instlatx64 (Alder Lake-P)
  CHECK_UARCH(arch, 0,  6,  9, 12, NA, "Tremont",         UARCH_TREMONT,          10) // LX*
  CHECK_UARCH(arch, 0,  6,  9, 13, NA, "Sunny Cove",      UARCH_SUNNY_COVE,       10) // LX*
  CHECK_UARCH(arch, 0,  6,  9, 14,  9, "Kaby Lake",       UARCH_KABY_LAKE,        14)
  CHECK_UARCH(arch, 0,  6,  9, 14, 10, "Coffee Lake",     UARCH_COFFEE_LAKE,      14)
  CHECK_UARCH(arch, 0,  6,  9, 14, 11, "Coffee Lake",     UARCH_COFFEE_LAKE,      14)
  CHECK_UARCH(arch, 0,  6,  9, 14, 12, "Coffee Lake",     UARCH_COFFEE_LAKE,      14)
  CHECK_UARCH(arch, 0,  6,  9, 14, 13, "Coffee Lake",     UARCH_COFFEE_LAKE,      14)
  CHECK_UARCH(arch, 0,  6, 10,  5, NA, "Comet Lake",      UARCH_COMET_LAKE,       14) // wikichip
  CHECK_UARCH(arch, 0,  6, 10,  6, NA, "Comet Lake",      UARCH_COMET_LAKE,       14) // instlatx64.atw.hu (i7-10710U)
  CHECK_UARCH(arch, 0,  6, 10,  7, NA, "Rocket Lake",     UARCH_ROCKET_LAKE,      14) // instlatx64.atw.hu (i7-11700K)
  CHECK_UARCH(arch, 0,  6, 11,  7, NA, "Raptor Lake",     UARCH_RAPTOR_LAKE,      10) // instlatx64.atw.hu (i5-13600K)
  CHECK_UARCH(arch, 0, 11,  0,  0, NA, "Knights Ferry",   UARCH_KNIGHTS_FERRY,    45) // found only on en.wikichip.org
  CHECK_UARCH(arch, 0, 11,  0,  1, NA, "Knights Corner",  UARCH_KNIGHTS_CORNER,   22)
  CHECK_UARCH(arch, 0, 15,  0,  0, NA, "Willamette",      UARCH_WILLAMETTE,      180)
  CHECK_UARCH(arch, 0, 15,  0,  1, NA, "Willamette",      UARCH_WILLAMETTE,      180)
  CHECK_UARCH(arch, 0, 15,  0,  2, NA, "Northwood",       UARCH_NORTHWOOD,       130)
  CHECK_UARCH(arch, 0, 15,  0,  3, NA, "Prescott",        UARCH_PRESCOTT,         90)
  CHECK_UARCH(arch, 0, 15,  0,  4, NA, "Prescott",        UARCH_PRESCOTT,         90)
  CHECK_UARCH(arch, 0, 15,  0,  6, NA, "Cedar Mill",      UARCH_CEDAR_MILL,       65)
  CHECK_UARCH(arch, 1, 15,  0,  0, NA, "Itanium2",        UARCH_ITANIUM2,        180)
  CHECK_UARCH(arch, 1, 15,  0,  1, NA, "Itanium2",        UARCH_ITANIUM2,        130)
  CHECK_UARCH(arch, 1, 15,  0,  2, NA, "Itanium2",        UARCH_ITANIUM2,        130)
  UARCH_END

  return arch;
}

// inspired in Todd Allen's decode_uarch_amd
struct uarch* get_uarch_from_cpuid_amd(uint32_t ef, uint32_t f, uint32_t em, uint32_t m, int s) {
  struct uarch* arch = (struct uarch*) malloc(sizeof(struct uarch));

  // NOTE: Process (last argument) is ignored, but included for compatiblity with
  // cpufetch
  //
  // EF: Extended Family                                          //
  // F:  Family                                                   //
  // EM: Extended Model                                           //
  // M: Model                                                     //
  // S: Stepping                                                  //
  // ------------------------------------------------------------ //
  //                 EF  F  EM   M   S                            //
  UARCH_START
  CHECK_UARCH(arch,  0,  4,  0,  3, NA, "Am486",       UARCH_AM486,      UNK)
  CHECK_UARCH(arch,  0,  4,  0,  7, NA, "Am486",       UARCH_AM486,      UNK)
  CHECK_UARCH(arch,  0,  4,  0,  8, NA, "Am486",       UARCH_AM486,      UNK)
  CHECK_UARCH(arch,  0,  4,  0,  9, NA, "Am486",       UARCH_AM486,      UNK)
  CHECK_UARCH(arch,  0,  4, NA, NA, NA, "Am5x86",      UARCH_AM5X86,     UNK)
  CHECK_UARCH(arch,  0,  5,  0,  6, NA, "K6",          UARCH_K6,         300)
  CHECK_UARCH(arch,  0,  5,  0,  7, NA, "K6",          UARCH_K6,         250) // *p from sandpile.org
  CHECK_UARCH(arch,  0,  5,  0, 10, NA, "K7",          UARCH_K7,         130) // Geode NX
  CHECK_UARCH(arch,  0,  5,  0, 13, NA, "K6",          UARCH_K6,          80) // *p from sandpile.org
  CHECK_UARCH(arch,  0,  5, NA, NA, NA, "K6",          UARCH_K6,         UNK)
  CHECK_UARCH(arch,  0,  6,  0,  1, NA, "K7",          UARCH_K7,         250)
  CHECK_UARCH(arch,  0,  6,  0,  2, NA, "K7",          UARCH_K7,         180)
  CHECK_UARCH(arch,  0,  6, NA, NA, NA, "K7",          UARCH_K7,         UNK)
  CHECK_UARCH(arch,  0, 15,  0,  4,  8, "K8",          UARCH_K8,         130)
  CHECK_UARCH(arch,  0, 15,  0,  4, NA, "K8",          UARCH_K8,         130)
  CHECK_UARCH(arch,  0, 15,  0,  5, NA, "K8",          UARCH_K8,         130)
  CHECK_UARCH(arch,  0, 15,  0,  7, NA, "K8",          UARCH_K8,         130)
  CHECK_UARCH(arch,  0, 15,  0,  8, NA, "K8",          UARCH_K8,         130)
  CHECK_UARCH(arch,  0, 15,  0, 11, NA, "K8",          UARCH_K8,         130)
  CHECK_UARCH(arch,  0, 15,  0, 12, NA, "K8",          UARCH_K8,         130)
  CHECK_UARCH(arch,  0, 15,  0, 14, NA, "K8",          UARCH_K8,         130)
  CHECK_UARCH(arch,  0, 15,  0, 15, NA, "K8",          UARCH_K8,         130)
  CHECK_UARCH(arch,  0, 15,  1,  4, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  1,  5, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  1,  7, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  1,  8, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  1, 11, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  1, 12, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  1, 15, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  2,  1, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  2,  3, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  2,  4, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  2,  5, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  2,  7, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  2, 11, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  2, 12, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  2, 15, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  4,  1, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  4,  3, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  4,  8, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  4, 11, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  4, 12, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  4, 15, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  5, 13, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  5, 15, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  0, 15,  6,  8, NA, "K8",          UARCH_K8,          65)
  CHECK_UARCH(arch,  0, 15,  6, 11, NA, "K8",          UARCH_K8,          65)
  CHECK_UARCH(arch,  0, 15,  6, 12, NA, "K8",          UARCH_K8,          65)
  CHECK_UARCH(arch,  0, 15,  6, 15, NA, "K8",          UARCH_K8,          65)
  CHECK_UARCH(arch,  0, 15,  7, 12, NA, "K8",          UARCH_K8,          65)
  CHECK_UARCH(arch,  0, 15,  7, 15, NA, "K8",          UARCH_K8,          65)
  CHECK_UARCH(arch,  0, 15, 12,  1, NA, "K8",          UARCH_K8,          90)
  CHECK_UARCH(arch,  1, 15,  0,  0, NA, "K10",         UARCH_K10,         65) // sandpile.org
  CHECK_UARCH(arch,  1, 15,  0,  2, NA, "K10",         UARCH_K10,         65)
  CHECK_UARCH(arch,  1, 15,  0,  4, NA, "K10",         UARCH_K10,         45)
  CHECK_UARCH(arch,  1, 15,  0,  5, NA, "K10",         UARCH_K10,         45)
  CHECK_UARCH(arch,  1, 15,  0,  6, NA, "K10",         UARCH_K10,         45)
  CHECK_UARCH(arch,  1, 15,  0,  8, NA, "K10",         UARCH_K10,         45)
  CHECK_UARCH(arch,  1, 15,  0,  9, NA, "K10",         UARCH_K10,         45)
  CHECK_UARCH(arch,  1, 15,  0, 10, NA, "K10",         UARCH_K10,         45)
  CHECK_UARCH(arch,  2, 15, NA, NA, NA, "Puma 2008",   UARCH_PUMA_2008,   65)
  CHECK_UARCH(arch,  3, 15, NA, NA, NA, "K10",         UARCH_K10,         32)
  CHECK_UARCH(arch,  5, 15, NA, NA, NA, "Bobcat",      UARCH_BOBCAT,      40)
  CHECK_UARCH(arch,  6, 15,  0,  0, NA, "Bulldozer",   UARCH_BULLDOZER,   32) // instlatx64 engr sample
  CHECK_UARCH(arch,  6, 15,  0,  1, NA, "Bulldozer",   UARCH_BULLDOZER,   32)
  CHECK_UARCH(arch,  6, 15,  0,  2, NA, "Piledriver",  UARCH_PILEDRIVER,  32)
  CHECK_UARCH(arch,  6, 15,  1,  0, NA, "Piledriver",  UARCH_PILEDRIVER,  32)
  CHECK_UARCH(arch,  6, 15,  1,  3, NA, "Piledriver",  UARCH_PILEDRIVER,  32)
  CHECK_UARCH(arch,  6, 15,  3,  0, NA, "Steamroller", UARCH_STEAMROLLER, 28)
  CHECK_UARCH(arch,  6, 15,  3,  8, NA, "Steamroller", UARCH_STEAMROLLER, 28)
  CHECK_UARCH(arch,  6, 15,  4,  0, NA, "Steamroller", UARCH_STEAMROLLER, 28) // Software Optimization Guide (15h) says it has the same iNAt latencies as (6,15),(3,x).
  CHECK_UARCH(arch,  6, 15,  6,  0, NA, "Excavator",   UARCH_EXCAVATOR,   28) // undocumented, but instlatx64 samples
  CHECK_UARCH(arch,  6, 15,  6,  5, NA, "Excavator",   UARCH_EXCAVATOR,   28) // undocumented, but sample from Alexandros Couloumbis
  CHECK_UARCH(arch,  6, 15,  7,  0, NA, "Excavator",   UARCH_EXCAVATOR,   28)
  CHECK_UARCH(arch,  7, 15,  0,  0, NA, "Jaguar",      UARCH_JAGUAR,      28)
  CHECK_UARCH(arch,  7, 15,  2,  6, NA, "Jaguar",      UARCH_JAGUAR,      28) // AMD Cato (Xbox One?)
  CHECK_UARCH(arch,  7, 15,  3,  0, NA, "Puma 2014",   UARCH_PUMA_2014,   28)
  CHECK_UARCH(arch,  8, 15,  0,  0, NA, "Zen",         UARCH_ZEN,         14) // instlatx64 engr sample
  CHECK_UARCH(arch,  8, 15,  0,  1, NA, "Zen",         UARCH_ZEN,         14)
  CHECK_UARCH(arch,  8, 15,  0,  8, NA, "Zen+",        UARCH_ZEN_PLUS,    12)
  CHECK_UARCH(arch,  8, 15,  1,  1, NA, "Zen",         UARCH_ZEN,         14) // found only on en.wikichip.org & instlatx64 examples
  CHECK_UARCH(arch,  8, 15,  1,  8, NA, "Zen+",        UARCH_ZEN_PLUS,    12) // found only on en.wikichip.org
  CHECK_UARCH(arch,  8, 15,  2,  0, NA, "Zen",         UARCH_ZEN,         14) // Dali, found on instlatx64 and en.wikichip.org
  CHECK_UARCH(arch,  8, 15,  3,  1, NA, "Zen 2",       UARCH_ZEN2,         7) // found only on en.wikichip.org
  CHECK_UARCH(arch,  8, 15,  4,  7, NA, "Zen 2",       UARCH_ZEN2,         7) // instlatx64 example (AMD 4700S)
  CHECK_UARCH(arch,  8, 15,  5,  0, NA, "Zen",         UARCH_ZEN,         14) // instlatx64 example (Subor Z+)
  CHECK_UARCH(arch,  8, 15,  6,  0, NA, "Zen 2",       UARCH_ZEN2,         7) // undocumented, geekbench.com example
  CHECK_UARCH(arch,  8, 15,  6,  8, NA, "Zen 2",       UARCH_ZEN2,         7) // found on instlatx64
  CHECK_UARCH(arch,  8, 15,  7,  1, NA, "Zen 2",       UARCH_ZEN2,         7) // samples from Steven Noonan and instlatx64
  CHECK_UARCH(arch, 10, 15,  0,  1, NA, "Zen 3",       UARCH_ZEN3,         7) // instlatx64
  CHECK_UARCH(arch, 10, 15,  2,  1, NA, "Zen 3",       UARCH_ZEN3,         7) // instlatx64
  CHECK_UARCH(arch, 10, 15,  5,  0, NA, "Zen 3",       UARCH_ZEN3,         7) // instlatx64
  UARCH_END

  return arch;
}

struct uarch* get_uarch_from_cpuid(struct cpu* cpu, uint32_t ef, uint32_t f, uint32_t em, uint32_t m, int s) {  
  if(is_cpu_intel(cpu))
    return get_uarch_from_cpuid_intel(ef, f, em, m, s);
  else if(is_cpu_amd(cpu))
    return get_uarch_from_cpuid_amd(ef, f, em, m, s);
  else {
    printf("Found invalid vendor in get_uarch_from_cpuid\n");
    return NULL;
  }
}

struct uarch* get_uarch(struct cpu* cpu) {
  uint32_t eax = 0x00000001;
  uint32_t ebx = 0;
  uint32_t ecx = 0;
  uint32_t edx = 0;
  
  cpuid(&eax, &ebx, &ecx, &edx);
   
  uint32_t stepping = eax & 0xF;
  uint32_t model = (eax >> 4) & 0xF;
  uint32_t emodel = (eax >> 16) & 0xF;
  uint32_t family = (eax >> 8) & 0xF;
  uint32_t efamily = (eax >> 20) & 0xFF;
  
  return get_uarch_from_cpuid(cpu, efamily, family, emodel, model, (int)stepping);
}

void free_uarch_struct(struct uarch* arch) {    
  free(arch->uarch_str);
  free(arch);
}
