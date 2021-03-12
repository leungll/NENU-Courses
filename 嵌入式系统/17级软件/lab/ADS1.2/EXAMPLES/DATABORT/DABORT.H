/*********************************************************************
 *
 * Data abort veneer: C header file
 * Copyright 1997 Advanced RISC Machines Limited. All rights reserved.
 *
 */

/*********************************************************************
 *
 * Abort models that may be supported by the data abort veneer,
 * depending on its assembly-time options.
 *
 */

#define DABORT_MODEL_BASERESTORED 0
  /* Processor always undoes base register writeback on data abort. */

#define DABORT_MODEL_BASEUPDATED  3
  /* Processor never undoes base register writeback on data abort. */

#define DABORT_MODEL_EARLYABORT   1
  /* Processor is an ARM6 configured for "early aborts". (Not a
   * legitimate abort model in newer processors.)
   */

/*********************************************************************
 *
 * Error codes that may be passed to the OS-specific handler as its
 * first parameter.
 *
 */

#define DABORT_ERROR_BAD_REQUEST      -1
  /* Disaster: OS-specific handler returned invalid value. */

#define DABORT_ERROR_NONE             0
  /* No errors occurred in data abort veneer. */

#define DABORT_ERROR_BASEEQINDEX_PRE  1
  /* Pre-indexed with writeback, base and index registers identical,
   * and data abort veneer does not contain code to handle this
   * special case).
   */

#define DABORT_ERROR_BASEEQINDEX_POST 2
  /* Post-indexed (implies writeback), and base and index registers
   * identical. (Architecturally UNPREDICTABLE, and data abort
   * recovery not always possible.)
   */

#define DABORT_ERROR_R15_WB           3
  /* Instruction attempts to do base register writeback to R15. */

#define DABORT_ERROR_BASE_R15         4
  /* LDM, STM or SWP instruction with a base register of R15. */

#define DABORT_ERROR_INDEX_R15        5
  /* Instruction attempts to use R15 as an index register. */

#define DABORT_ERROR_LOAD_WB          6
  /* Instruction attempts to load its own base register and do base
   * register writeback to it as well.
   */

#define DABORT_ERROR_LDMSTM_EMPTY     7
  /* Instruction is an LDM, STM, PUSH or POP with an empty register
   * list.
   */

#define DABORT_ERROR_USERBANK_WB      8
  /* Instruction is a "user bank" LDM or STM and specifies base
   * register writeback.
   */

#define DABORT_ERROR_BAD_INSTR        9
  /* Instruction does not appear to be a load/store instruction
   * (possibly due to the processor being designed to a newer
   * architecture version than the data abort veneer).
   */

/*********************************************************************
 *
 * Special values that may be returned by the OS-specific handler
 * (assuming the data abort veneer has been assembled with appropriate
 * options).
 *
 */

#define DABORT_RETVAL_NORMAL 0x0
  /* To return to original program */

#define DABORT_RETVAL_UNDEF  0x4
  /* To fake an undefined instruction trap */

#define DABORT_RETVAL_TONEXT 0x10
  /* To call a chained data abort handler */

/*********************************************************************
 *
 * End of file "dabort.h"
 *
 */
