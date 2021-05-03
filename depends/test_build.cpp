#include <iostream>
#include <windows>
#include <string>

using namespace std;

int main()
{
    string projectPath;
    cout << "Input project path(.vsxproj where)"
    cin >> projectPath;
    string head = "msbuild ";
    string foot = " /p:Configuration=""release""";
    c.append(head);
    c.append(projectPath);
    c.append(foot);
    system(c);
}