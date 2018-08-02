genrule(
	name = "libpngconf",
	srcs = [
		"scripts/pnglibconf.h.prebuilt"
	],
	outs = [
		"pnglibconf.h",
	],
	cmd = "cp $(location scripts/pnglibconf.h.prebuilt) $(location pnglibconf.h)",
)

cc_library(
    name = "main",
    srcs = [
        "png.c",
        "pngdebug.h",
        "pngerror.c",
        "pngget.c",
        "pnginfo.h",
        "pnglibconf.h",
        "pngmem.c",
        "pngpread.c",
        "pngpriv.h",
        "pngread.c",
        "pngrio.c",
        "pngrtran.c",
        "pngrutil.c",
        "pngset.c",
        "pngstruct.h",
        "pngtrans.c",
        "pngwio.c",
        "pngwrite.c",
        "pngwtran.c",
        "pngwutil.c",
    ],
    hdrs = [
        "png.h",
        "pngconf.h",
    ],
    includes = [
    	"."
    ],
    linkopts = ["-lm", "-lz"],
    visibility = ["//visibility:public"],
)