#include <iostream>

extern "C" double gmx11_set_caption(const char * caption);

int main() {
    const char *s = "窗口标题 - 中文测试";
    double r = gmx11_set_caption(s);
    std::cout << "gmx11_set_caption returned: " << r << std::endl;
    return (r == 1) ? 0 : 1;
}
