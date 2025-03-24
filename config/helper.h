#pragma once

// CREDITS : https://github.com/toniz4/zmk-config

#define TAPPING_TERM 175
#define ZMK_HELPER_STRINGIFY(x) #x
// #define OS_UNICODE_LEAD &macro_tap &kp LS(LC(U))   // Linux
// #define OS_UNICODE_TRAIL &macro_tap &kp SPACE     // Linux

#define AC_MODMORPH(name, ac_binding, shifted_ac_binding) \
    / { \
        behaviors { \
            name: name { \
                compatible = "zmk,behavior-mod-morph"; \
                label = ZMK_HELPER_STRINGIFY(AC_MORPH_ ## name); \
                #binding-cells = <0>; \
                bindings = <uc_binding>, <shifted_uc_binding>; \
                mods = <(MOD_LSFT|MOD_RSFT)>; \
            }; \
        }; \
    };

#define AC_MACRO(name, letter, accent) \
    / { \
        macros { \
            name: name { \
                compatible = "zmk,behavior-macro"; \
                label = ZMK_HELPER_STRINGIFY(AC_MACRO_ ## name); \
                wait-ms = <10>; \
                tap-ms = <10>; \
                #binding-cells = <0>; \
                bindings = <&kp accent &kp letter>;\
            }; \
        }; \
    };


#define AC_KEY(name, letter, accent) \
    / { \
        macros { \
            name ## _down: name ## _down { \
                compatible = "zmk,behavior-macro"; \
                label = ZMK_HELPER_STRINGIFY(AC_MACRO_ ## name ## _down); \
                wait-ms = <10>; \
                tap-ms = <10>; \
                #binding-cells = <0>; \
                bindings = <&kp accent &kp letter>;\
            }; \
            name ## _up: name ## _up { \
                compatible = "zmk,behavior-macro"; \
                label = ZMK_HELPER_STRINGIFY(AC_MACRO_ ## name ## _up); \
                wait-ms = <10>; \
                tap-ms = <10>; \
                #binding-cells = <0>; \
                bindings = <&kp accent &kp LS(letter)>;	\
            }; \
        }; \
        behaviors { \
            name: name { \
                compatible = "zmk,behavior-mod-morph"; \
                label = ZMK_HELPER_STRINGIFY(AC_MORPH_ ## name); \
                #binding-cells = <0>; \
                bindings = <&name ## _down>, <&name ## _up>; \
                mods = <(MOD_LSFT|MOD_RSFT)>; \
            }; \
        }; \
    };

#define UNDEAD_KEY(name, key) \
  / { \
        macros { \
            name: name { \
                compatible = "zmk,behavior-macro"; \
                label = ZMK_HELPER_STRINGIFY(UNDEAD_MACRO_ ## name); \
                wait-ms = <10>; \
                tap-ms = <10>; \
                #binding-cells = <0>; \
                bindings = <&kp key &kp SPACE>; \
            }; \
        }; \
    };


// UNICODE
#define UC_MACRO(name, unicode_bindings) \
    / { \
        macros { \
            name: name { \
                compatible = "zmk,behavior-macro"; \
                wait-ms = <0>; \
                tap-ms = <0>; \
                #binding-cells = <0>; \
                bindings = <OS_UNICODE_LEAD>, <&macro_tap unicode_bindings>, <OS_UNICODE_TRAIL>; \
            }; \
        }; \
    };

#define UC_MODMORPH(name, uc_binding, shifted_uc_binding) \
    / { \
        behaviors { \
            name: name { \
                compatible = "zmk,behavior-mod-morph"; \
                #binding-cells = <0>; \
                bindings = <uc_binding>, <shifted_uc_binding>; \
                mods = <(MOD_LSFT|MOD_RSFT)>; \
            }; \
        }; \
    };

#define ZMK_UNICODE_SINGLE(name, L0, L1, L2, L3) \
    UC_MACRO(name ## _lower, &kp L0 &kp L1 &kp L2 &kp L3) \
    UC_MODMORPH(name, &name ## _lower, &none)

#define ZMK_UNICODE_PAIR(name, L0, L1, L2, L3, U0, U1, U2, U3) \
    UC_MACRO(name ## _lower, &kp L0 &kp L1 &kp L2 &kp L3) \
    UC_MACRO(name ## _upper, &kp U0 &kp U1 &kp U2 &kp U3) \
    UC_MODMORPH(name, &name ## _lower, &name ## _upper)
