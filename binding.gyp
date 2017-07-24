{
    "targets": [
        {
            "target_name": "node-mmap",
            "sources": [
                "src/module.cc"
            ],
            "include_dirs": [
                "<!(node -e \"require('nan')\")",
                "<!(node -e \"require('nnu')\")",
                "deps/hll/src"
            ],
            "conditions": [
                ["OS == 'win'", {
                    "sources": [
                        "src/mmap_win.cc"
                    ]
                }],
                ["OS != 'win'", {
                    "sources": [
                        "src/mmap_posix.cc"
                    ]
                }]
            ]
        }
    ]
}