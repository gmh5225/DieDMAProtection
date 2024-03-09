#pragma once
#include "cpp.h"

#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16
#define IMAGE_DOS_SIGNATURE                 0x5A4D      // MZ
#define IMAGE_NT_SIGNATURE                  0x00004550  // PE00
#define IMAGE_SIZEOF_SHORT_NAME             8
#define IMAGE_SCN_CNT_UNINITIALIZED_DATA    0x00000080  // Section contains uninitialized data.
#define IMAGE_SCN_MEM_WRITE                 0x80000000
#define UNW_FLAG_EHANDLER  1
#define IMAGE_DIRECTORY_ENTRY_EXPORT	0
#define IMAGE_DIRECTORY_ENTRY_IMPORT	1
#define IMAGE_DIRECTORY_ENTRY_EXCEPTION      3
#define IMAGE_DIRECTORY_ENTRY_BASERELOC       5
#define IMAGE_REL_BASED_DIR64                   10

#define IMAGE_FIRST_SECTION( ntheader ) ((PIMAGE_SECTION_HEADER)        \
    ((ULONG_PTR)(ntheader) +                                            \
     FIELD_OFFSET( IMAGE_NT_HEADERS, OptionalHeader ) +                 \
     ((ntheader))->FileHeader.SizeOfOptionalHeader   \
    ))

#define RELOC_FLAG64(RelInfo) ((RelInfo >> 0x0C) == IMAGE_REL_BASED_DIR64)
#define RELOC_FLAG RELOC_FLAG64

#define IMAGE_ORDINAL_FLAG64 0x8000000000000000ULL

#define IMAGE_ORDINAL_FLAG32 0x80000000

#define IMAGE_ORDINAL64(Ordinal) (Ordinal & 0xffff)

#define IMAGE_ORDINAL32(Ordinal) (Ordinal & 0xffff)

#define IMAGE_SNAP_BY_ORDINAL64(Ordinal) ((Ordinal & IMAGE_ORDINAL_FLAG64) != 0)

#define IMAGE_SNAP_BY_ORDINAL32(Ordinal) ((Ordinal & IMAGE_ORDINAL_FLAG32) != 0)

#define IMAGE_SNAP_BY_ORDINAL IMAGE_SNAP_BY_ORDINAL64

#define IS_MZ(Base) (*(USHORT*)Base == 'MZ')

#define IMAGE_SCN_MEM_EXECUTE 0x20000000

typedef struct _IMAGE_BASE_RELOCATION {
    ULONG VirtualAddress;
    ULONG SizeOfBlock;
} IMAGE_BASE_RELOCATION, * PIMAGE_BASE_RELOCATION;

typedef struct _IMAGE_IMPORT_DESCRIPTOR {
    union {
        ULONG   Characteristics;
        ULONG   OriginalFirstThunk;
    } DUMMYUNIONNAME;
    ULONG   TimeDateStamp;
    ULONG   ForwarderChain;
    ULONG   Name;
    ULONG   FirstThunk;
} IMAGE_IMPORT_DESCRIPTOR, * PIMAGE_IMPORT_DESCRIPTOR;

typedef struct _IMAGE_IMPORT_BY_NAME {
    USHORT  Hint;
    UCHAR   Name[1];
} IMAGE_IMPORT_BY_NAME, * PIMAGE_IMPORT_BY_NAME;

typedef struct _IMAGE_EXPORT_DIRECTORY {
    ULONG Characteristics;
    ULONG TimeDateStamp;
    USHORT MajorVersion;
    USHORT MinorVersion;
    ULONG Name;
    ULONG Base;
    ULONG NumberOfFunctions;
    ULONG NumberOfNames;
    ULONG AddressOfFunctions;
    ULONG AddressOfNames;
    ULONG AddressOfNameOrdinals;
} IMAGE_EXPORT_DIRECTORY, * PIMAGE_EXPORT_DIRECTORY;

typedef struct _SCOPE_RECORD {
    UINT32 BeginAddress;
    UINT32 EndAddress;
    UINT32 HandlerAddress;
    UINT32 JumpTarget;
} SCOPE_RECORD;

typedef struct _SCOPE_TABLE {
    UINT32 Count;
    SCOPE_RECORD ScopeRecords[1];
} SCOPE_TABLE;

typedef struct _RUNTIME_FUNCTION {
    UINT32 BeginAddress;
    UINT32 EndAddress;
    UINT32 UnwindData;
} RUNTIME_FUNCTION;

typedef union _UNWIND_CODE {
    UINT8 CodeOffset;
    UINT8 UnwindOp : 4;
    UINT8 OpInfo : 4;
    UINT16 FrameOffset;
} UNWIND_CODE;

typedef struct _UNWIND_INFO {
    UINT8 Version : 3;
    UINT8 Flags : 5;
    UINT8 SizeOfProlog;
    UINT8 CountOfCodes;
    UINT8 FrameRegister : 4;
    UINT8 FrameOffset : 4;
    UNWIND_CODE UnwindCode[1];

    union {
        UINT32 ExceptionHandler;
        UINT32 FunctionEntry;
    };

    UINT32 ExceptionData[1];
} UNWIND_INFO;

typedef struct _IMAGE_DOS_HEADER {      // DOS .EXE header
    UINT16   e_magic;                     // Magic number
    UINT16   e_cblp;                      // UINT8s on last page of file
    UINT16   e_cp;                        // Pages in file
    UINT16   e_crlc;                      // Relocations
    UINT16   e_cparhdr;                   // Size of header in paragraphs
    UINT16   e_minalloc;                  // Minimum extra paragraphs needed
    UINT16   e_maxalloc;                  // Maximum extra paragraphs needed
    UINT16   e_ss;                        // Initial (relative) SS value
    UINT16   e_sp;                        // Initial SP value
    UINT16   e_csum;                      // Checksum
    UINT16   e_ip;                        // Initial IP value
    UINT16   e_cs;                        // Initial (relative) CS value
    UINT16   e_lfarlc;                    // File address of relocation table
    UINT16   e_ovno;                      // Overlay number
    UINT16   e_res[4];                    // Reserved words
    UINT16   e_oemid;                     // OEM identifier (for e_oeminfo)
    UINT16   e_oeminfo;                   // OEM information; e_oemid specific
    UINT16   e_res2[10];                  // Reserved words
    UINT32   e_lfanew;                    // File address of new exe header
} IMAGE_DOS_HEADER, * PIMAGE_DOS_HEADER;

typedef struct _IMAGE_FILE_HEADER {
    UINT16    Machine;
    UINT16    NumberOfSections;
    UINT32   TimeDateStamp;
    UINT32   PointerToSymbolTable;
    UINT32   NumberOfSymbols;
    UINT16    SizeOfOptionalHeader;
    UINT16    Characteristics;
} IMAGE_FILE_HEADER, * PIMAGE_FILE_HEADER;

typedef struct _IMAGE_DATA_DIRECTORY {
    UINT32   VirtualAddress;
    UINT32   Size;
} IMAGE_DATA_DIRECTORY, * PIMAGE_DATA_DIRECTORY;

typedef struct _IMAGE_OPTIONAL_HEADER64 {
    UINT16        Magic;
    UINT8        MajorLinkerVersion;
    UINT8        MinorLinkerVersion;
    UINT32       SizeOfCode;
    UINT32       SizeOfInitializedData;
    UINT32       SizeOfUninitializedData;
    UINT32       AddressOfEntryPoint;
    UINT32       BaseOfCode;
    ULONGLONG   ImageBase;
    UINT32       SectionAlignment;
    UINT32       FileAlignment;
    UINT16        MajorOperatingSystemVersion;
    UINT16        MinorOperatingSystemVersion;
    UINT16        MajorImageVersion;
    UINT16        MinorImageVersion;
    UINT16        MajorSubsystemVersion;
    UINT16        MinorSubsystemVersion;
    UINT32       Win32VersionValue;
    UINT32       SizeOfImage;
    UINT32       SizeOfHeaders;
    UINT32       CheckSum;
    UINT16        Subsystem;
    UINT16        DllCharacteristics;
    ULONGLONG   SizeOfStackReserve;
    ULONGLONG   SizeOfStackCommit;
    ULONGLONG   SizeOfHeapReserve;
    ULONGLONG   SizeOfHeapCommit;
    UINT16       LoaderFlags;
    UINT32       NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER64, * PIMAGE_OPTIONAL_HEADER64;

typedef struct _IMAGE_NT_HEADERS64 {
    UINT32 Signature;
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER64 OptionalHeader;
} IMAGE_NT_HEADERS64, * PIMAGE_NT_HEADERS64;

typedef struct _IMAGE_SECTION_HEADER {
    UINT8    Name[IMAGE_SIZEOF_SHORT_NAME];
    union {
        UINT32   PhysicalAddress;
        UINT32   VirtualSize;
    } Misc;
    UINT32   VirtualAddress;
    UINT32   SizeOfRawData;
    UINT32   PointerToRawData;
    UINT32   PointerToRelocations;
    UINT32   PointerToLinenumbers;
    UINT16    NumberOfRelocations;
    UINT16    NumberOfLinenumbers;
    UINT32   Characteristics;
} IMAGE_SECTION_HEADER, * PIMAGE_SECTION_HEADER;

typedef IMAGE_NT_HEADERS64                  IMAGE_NT_HEADERS;
