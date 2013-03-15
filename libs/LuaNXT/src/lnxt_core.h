#ifndef LNXT_H_
#define LNXT_H_

#ifdef LNXT_OWN
   #define LNXT_API 
#else
   #define LNXT_API extern 
#endif /* LNXT_OWN */

enum NXT_COMMAND_TYPE {
    NXT_DIRECT_RET             = 0x00,
    NXT_SYSTEM_RET             = 0x01,
    NXT_REPLY                  = 0x02,
    NXT_DIRECT_NORET           = 0x80,
    NXT_SYSTEM_NORET           = 0x81
};

enum NXT_DIRECT_COMMAND {
    NXT_STARTPROGRAM           = 0x00,
    NXT_STOPPROGRAM            = 0x01,
    NXT_PLAYSOUNDFILE          = 0x02,
    NXT_PLAYTONE               = 0x03,
    NXT_SETOUTPUTSTATE         = 0x04,
    NXT_SETINPUTMODE           = 0x05,
    NXT_GETOUTPUTSTATE         = 0x06,
    NXT_GETINPUTVALUES         = 0x07, 
    NXT_RESETINPUTSCALEDVALUE  = 0x08,
    NXT_MESSAGEWRITE           = 0x09,
    NXT_RESETMOTORPOSISTION    = 0x0A,
    NXT_GETBATTERYLEVEL        = 0x0B,
    NXT_STOPSOUNDPLAYBACK      = 0x0C,
    NXT_KEEPALIVE              = 0x0D,
    NXT_LSGETSTATUS            = 0x0E,
    NXT_LSWRITE                = 0x0F, 
    NXT_LSREAD                 = 0x10,
    NXT_GETCURRENTPROGRAM      = 0x11,
    NXT_MESSAGEREAD            = 0x13
};

enum NXT_SYSTEM_COMMAND {
    NXT_GETFIRMWAREVERSION     = 0x88,
    NXT_BOOT                   = 0x97,
    NXT_SETBRICKNAME           = 0x98,
    NXT_GETDEVICEINFO          = 0x9B
};

enum NXT_OUTPUT_PORT {
    NXT_OUTPORT_A              = 0x00,
    NXT_OUTPORT_B              = 0x01,
    NXT_OUTPORT_C              = 0x02,
    NXT_OUTPORT_ALL            = 0xFF
};

enum NXT_NUMBER_FORMAT {
    NXT_UBYTE                      = 0x00,
    NXT_SBYTE                      = 0x01,
    NXT_UWORD                      = 0x02,
    NXT_SWORD                      = 0x03,
    NXT_ULONG                      = 0x04,
    NXT_SLONG                      = 0x05
};                              

/**
 * @brief Error code mapping to message strings.
 *
 */
typedef struct __nxt_error {
    unsigned char error_code;
    char * msg;
} nxt_error;

nxt_error NXT_ERROR[]=
{                
    { 0x20 , "Pending communication transaction in progress"       },
    { 0x40 , "Specified mailbox queue is empty"                    },
    { 0x81 , "No more handles"                                     },
    { 0x82 , "No space"                                            },
    { 0x83 , "No more files"                                       },
    { 0x84 , "End of file expected"                                },
    { 0x85 , "End of file"                                         },
    { 0x86 , "Not a linear file"                                   },
    { 0x87 , "File not found"                                      },
    { 0x88 , "Handle all ready closed"                             },
    { 0x89 , "No linear space"                                     },
    { 0x8A , "Undefined error"                                     },
    { 0x8B , "File is busy"                                        },
    { 0x8C , "No write buffers"                                    },
    { 0x8D , "Append not possible"                                 },
    { 0x8E , "File is full"                                        },
    { 0x8F , "File exists"                                         },
    { 0x90 , "Module not found"                                    },
    { 0x91 , "Out of boundary"                                     },
    { 0x92 , "Illegal file name"                                   },
    { 0x93 , "Illegal handle"                                      },
    { 0xBD , "Request failed (i.e. specified file not found)"      },
    { 0xBE , "Unknown command opcode"                              },
    { 0xBF , "Insane packet"                                       },
    { 0xC0 , "Data contains out-of-range values"                   },
    { 0xDD , "Communication bus error"                             },
    { 0xDE , "No free memory in communication buffer"              },
    { 0xDF , "Specified channel/connection is not valid"           },
    { 0xE0 , "Specified channel/connection not configured or busy" },
    { 0xEC , "No active program"                                   },
    { 0xED , "Illegal size specified"                              },
    { 0xEE , "Illegal mailbox queue ID specified"                  },
    { 0xEF , "Attempted to access invalid field of a structure"    },
    { 0xF0 , "Bad input or output specified"                       },
    { 0xFB , "Insufficient memory available"                       },
    { 0xFF , "Bad arguments"                                       },
    { 0x00 , NULL                                                  }
};

#endif /* LNXT_H_ */

