;
; Copyright (C) ARM Limited 1999. All rights reserved.
;
; This section serves two purposes:
;
; 1.  It defines magic string "*** Service ***" that is
;     immediately followed by the offset of the service
;     registration function for this application.
;
; 2.  It defines the (ZI) data size for this application.
;     Reference to bss_size from the application forces
;     the inclusion of this section in the application. 

    AREA ApplicationHeader, READONLY

    EXPORT    application_header
    EXPORT    bss_size

    IMPORT    register_services
    IMPORT    |Image$$ER_ZI$$ZI$$Length|

application_header
    DCB       "*** Service ***", 0
    DCD       register_services - {PC}
bss_size
    DCD       |Image$$ER_ZI$$ZI$$Length|

    END

