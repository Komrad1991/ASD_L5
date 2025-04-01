#include <queue>
#include <deque>
#include "myQueue.h"
#include <random>
#include <chrono>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <fstream>

using namespace std::chrono;

int main()
{
	int progon = 10;
	std::cout << "TIME MESURE: " << std::endl;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::vector<long long> nums;
	std::vector<long long> nums2;
	std::uniform_int_distribution<> dis2(1000, 1000000);
	for (int i = 0; i < 10000; i++)
	{
		nums.push_back(dis2(gen));
	}
	for (int i = 0; i < 100; i++)
	{
		nums2.push_back(dis2(gen));
	}
	{
		long long duration = 0;
		for (int i = 0; i < progon; i++)
		{
			
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			myQueue<long long,std::vector<long long>> q(nums);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		}
		std::cout << "myQueue create time: " << duration / progon << std::endl;
	}
	{
		long long duration = 0;
		for (int i = 0; i < progon; i++)
		{
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			
			for (int j = 0; j < nums.size(); j++)
			{
				std::priority_queue<long long, std::vector<long long>,std::less<long long>> q(nums.begin(),nums.end());
			}
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		}
		std::cout << "std create time: " << duration / progon << std::endl;
	}
	{
		long long duration = 0;
		for (int i = 0; i < progon; i++)
		{
			myQueue<long long, std::vector<long long>> q(nums);
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			for (int j = 0; j < nums.size()/4; j++)
			{
				q.top();
				q.pop();

			}
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		}
		std::cout << "myQueue top time: " << duration / progon << std::endl;
	}
	{
		long long duration = 0;
		for (int i = 0; i < progon; i++)
		{
			std::priority_queue<long long, std::vector<long long>, std::less<long long>> q(nums.begin(), nums.end());
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			for (int j = 0; j < nums.size()/4; j++)
			{
				q.top();
				q.pop();
			}
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		}
		std::cout << "std top time: " << duration / progon << std::endl;
	}
	{
		long long duration = 0;
		for (int i = 0; i < progon; i++)
		{
			myQueue<long long, std::vector<long long>> q(nums);
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			for (int j = 0; j < nums2.size(); j++)
			{
				q.insert(nums2[j]);

			}
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		}
		std::cout << "myQueue insert 100 time: " << duration / progon << std::endl;
	}
	{
		long long duration = 0;
		for (int i = 0; i < progon; i++)
		{
			std::priority_queue<long long, std::vector<long long>, std::less<long long>> q(nums.begin(), nums.end());
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
			for (int j = 0; j < nums2.size(); j++)
			{
				q.push(nums2[i]);
			}
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
			duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		}
		std::cout << "std insert 100 time: " << duration / progon << std::endl;
	}
	std::cout << "---------------" << std::endl;
	myBinQueue<std::string> my;
	std::priority_queue<std::string> standart;
	std::string word;
	{
		long long duration = 0;
		std::fstream file;
		file.open("big.txt");
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		while (file >> word)
		{
			standart.push(word);
		}
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		std::cout << "std big.txt time and word: " << duration << " " << standart.top() << std::endl;
	}
	{
		long long duration = 0;
		std::fstream file;
		file.open("big.txt");
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		while (file >> word)
		{
			my.insert(word);
		}
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		std::cout << "myBin big.txt time and word: " << duration << " " << my.top() << std::endl;
	}
	
}