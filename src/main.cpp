# include "VirtualMashine.hpp"

int         main(void)
{
    VirtualMashine vm;

    vm.readFromConsole();
    system("leaks -q test");
    return (0);
}
