# include "VirtualMashine.hpp"
# include <fstream>

int         main(int argc, char **argv)
{
    VirtualMashine vm;
    if (argc > 1){
        std::filebuf fb;
        if (fb.open (argv[1], std::ios::in)){
            std::istream is(&fb);
            vm.read(is);
        }
    }
    else
        vm.read(std::cin);
    system("leaks -q avm");
    return (0);
}
