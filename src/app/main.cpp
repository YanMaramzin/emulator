#include <iostream>
import core.logger.console;
import core.logger;

int main()
{
    ConsoleLogger logger;
    logger.log(LogLevel::Warning, "Hello World!");
    std::cout << "Hello World!\n";
}