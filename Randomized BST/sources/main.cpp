#include "RBST.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
int main(int argc, char* argv[])
{
	srand(time(NULL));
	std::string text;
	std::string key;
	std::string value;
	//std::ifstream fin("commands.txt");
	std::ofstream fout("result.txt");
	std::ofstream fout_("runtimeRBST.txt");
	bool flag = true;

	RBST mytree;
	if (argc != 3)  return 1;
	else {
		std::ifstream fin(argv[1]);
	        std::ofstream fout(argv[2]);
		if (!fin.is_open())
		std::cout << "Could not open file\n";
		else {
	int counter1 = 0;
	int counter2 = 0;
	int counter3 = 0;
	unsigned int sum1 = 0;
	unsigned int sum2 = 0;
	unsigned int sum3 = 0;
	auto now1 = std::chrono::high_resolution_clock::now();
	auto now2 = std::chrono::high_resolution_clock::now();
	auto now3 = std::chrono::high_resolution_clock::now();
	auto elapsed1 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - now1);
	auto elapsed2 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - now2);
	auto elapsed3 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - now3);
			while (!fin.eof())
			{
				std::getline(fin, text);
				if (text.find("add") != std::string::npos)
				{
					if (text[3] == ' ')
					{
						for (int i = 4; i < text.length(); i++)
						{
							if (text[i] != ' ' && isdigit(text[i]) && flag == true) {
								key += text[i];

							}
							else if (text[i] == ' ')
							{
								flag = false;
							}
							else
							{
								if (text[i] != ' ' && isdigit(text[i]) && flag == false)
									value += text[i];
								else fout << "error" << std::endl;
							};
						}
						counter1++;
						if (!key.empty() & !value.empty())
						{
							now1 = std::chrono::high_resolution_clock::now();
							mytree.insert(atoi(key.c_str()), atoi(value.c_str()));
							elapsed1 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - now1);
							sum1 += elapsed1.count();
						}
						else  fout << "error" << std::endl;
					}
					else fout << "error" << std::endl;
				}
				if (text.find("delete") != std::string::npos)
				{
					if (text[6] == ' ')
					{
						for (int i = 7; i < text.length(); i++)
						{
							key += text[i];
						}
						counter2++;
						now2 = std::chrono::high_resolution_clock::now();
						bool it = mytree.remove(atoi(key.c_str()));
						elapsed2 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - now2);
						sum2 += elapsed2.count();
						if (it == true) { ; }
						else fout << "error" << std::endl;
					}
					else fout << "error" << std::endl;
				}
				if (text == "print")
				{
					mytree.levelTraversal(fout);
				}
				if (text == "inorder")
				{
					mytree.inorder(fout);
				}
				if (text == "preorder")
				{
					mytree.preorder(fout);
				}
				if (text == "postorder")
				{
					mytree.postorder(fout);
				}
				if (text.find("search") != std::string::npos)
				{
					if (text[6] == ' ')
					{
						for (int i = 7; i < text.length(); i++)
						{
							key += text[i];
						}
						counter3++;
						now3 = std::chrono::high_resolution_clock::now();
						int it = mytree.find(atoi(key.c_str()));
						elapsed3 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - now3);
						sum3 += elapsed3.count();
						if (it) fout << it << std::endl;
						else fout << "error" << std::endl;
					}
					else fout << "error" << std::endl;
				}
				if (text == "min")
				{
					int it = mytree.findMin();
					if (it != false) fout << it << std::endl;
					else fout << "error" << std::endl;
				}
				if (text == "max")
				{
					int it = mytree.findMax();
					if (it != false) fout << it << std::endl;
					else fout << "error" << std::endl;
				}
				if (!key.empty())	key.clear();
				if (!value.empty()) value.clear();
				flag = true;
			}

			if (counter1) fout_ << "average insertion time: " << sum1 / counter1 << "ns.\n";
			if (counter2) fout_ << "average deletion time: " << sum2 / counter2 << "ns. \n";
			if (counter3) fout_ << "average searching time: " << sum3 / counter3 << "ns. \n";
		}
	}
	system("pause");
	return 0;



}

