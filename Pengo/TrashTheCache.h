#ifndef TRASHTHECACHE_H
#define TRASHTHECACHE_H

#include <mutex>
#include <vector>
#include <map>
#include <iostream>

#include <Component.h>

class TrashTheCache final : public dae::Component
{
public:
	explicit TrashTheCache(dae::GameObject* pOwner) : Component(pOwner) {}
	~TrashTheCache() override;

	TrashTheCache(const TrashTheCache& other) = delete;
	TrashTheCache& operator=(const TrashTheCache& rhs) = delete;
	TrashTheCache(TrashTheCache&& other) = delete;
	TrashTheCache& operator=(TrashTheCache&& rhs) = delete;

	void Start() override;
	void OnGui() override;

private:
	std::atomic_bool m_CalculateExercise1{ false }, m_CalculateExercise2{ false }, m_CalculateExercise2Alt{ false }, m_KillAllThreads{ false };
	int m_AmountOfIterations{ 20 }, m_MaxStepSize{ 1024 }, m_ArraySize{ 10'000'000 };
	const std::vector<const char*> m_TimeSteps{ "1","2","4","8","16","32","64","256","512","1024" };
	const std::vector<double> m_Ticks{ 1,2,3,4,5,6,7,8,9,10 };
	std::vector<double> m_ResultsInt{};
	std::vector<double> m_ResultsNoPointer{};
	std::vector<double> m_ResultsWithPointer{};

	std::jthread m_Exercise1Thread, m_Exercise2Thread, m_Exercise2AltThread;

	struct Transform
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
	};
	class NoPointer
	{
	public:
		Transform local;
		int id = 0;
	};
	class WithPointer
	{
	public:
		Transform* local;
		int id = 0;
	};

	template <typename T>
	std::map<int, std::vector<float>> GatherData(bool outputValues);
	std::map<int, std::vector<float>> GatherData(bool outputValues) const;
	std::vector<double> AverageResult(std::map<int, std::vector<float>> data) const;
};

template <typename T>
std::map<int, std::vector<float>> TrashTheCache::GatherData(bool outputValues)
{
	std::vector<T> v;
	auto t = T();
	v.assign(m_ArraySize, t);

	std::map<int, std::vector<float>> data;

	for (int stepSize = 1; stepSize <= m_MaxStepSize; stepSize *= 2)
	{
		if (outputValues)
			std::cout << "stepSize = " << stepSize << '\n';

		for (int j = 0; j < m_AmountOfIterations; ++j)
		{
			auto start = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < static_cast<int>(v.size()); i += stepSize)
			{
				v[i].id *= 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			const auto time = std::chrono::duration<float>(end - start).count();

			if (outputValues)
				std::cout << time << " seconds\n";

			data[stepSize].push_back(time);
		}

		if (outputValues)
			std::cout << "\n\n";
	}

	return data;
}

#endif // TRASHTHECACHE_H
