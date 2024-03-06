#include "stdafx.h"
#include "TrashTheCache.h"

#include <ranges>
#include <thread>

TrashTheCache::~TrashTheCache()
{
    m_KillAllThreads = true;
}

void TrashTheCache::Start()
{
    m_Exercise1Thread = std::jthread([&]()
        {
            while (m_KillAllThreads == false)
            {
	            if (m_CalculateExercise1)
	            {
                    m_ResultsInt.clear();

                    const auto data = GatherData(false);
                    m_ResultsInt = AverageResult(data);

                    m_CalculateExercise1 = false;
	            }
            }
        });
    m_Exercise2Thread = std::jthread([&]()
        {
            while (m_KillAllThreads == false)
            {
	            if (m_CalculateExercise2)
	            {
                    m_ResultsNoPointer.clear();

                    const auto data = GatherData<NoPointer>(false);
                    m_ResultsNoPointer = AverageResult(data);

                    m_CalculateExercise2 = false;
	            }
            }
        });
    m_Exercise2AltThread = std::jthread([&]()
        {
            while (m_KillAllThreads == false)
            {
	            if (m_CalculateExercise2Alt)
	            {
                    m_ResultsWithPointer.clear();

                    const auto data = GatherData<WithPointer>(false);
                    m_ResultsWithPointer = AverageResult(data);

                    m_CalculateExercise2Alt = false;
	            }
            }
        });
}

void TrashTheCache::OnGui()
{
	{
		ImGui::Begin("Exercise 1");

        ImGui::Text("Filling a vector with %i integers", m_ArraySize);

        if (m_CalculateExercise1 == false)
            m_CalculateExercise1 = ImGui::Button("Trash the cache");
        else
            ImGui::Text("Waiting for it...");

    	if (m_ResultsInt.empty() == false && ImPlot::BeginPlot("Integers")) 
        {
            ImPlot::SetupAxis(ImAxis_X1, "step size", ImPlotAxisFlags_Lock);
            ImPlot::SetupAxis(ImAxis_Y1, "time in seconds", ImPlotAxisFlags_Lock);
            ImPlot::SetupAxisLimits(ImAxis_X1, 0.5, 10.5);
            ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 0.01);
            ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
            ImPlot::SetupAxisTicks(ImAxis_X1, m_Ticks.data(), static_cast<int>(m_Ticks.size()), m_TimeSteps.data());
    		ImPlot::PlotLine("integers", m_Ticks.data(), m_ResultsInt.data(), static_cast<int>(m_Ticks.size()));
    		ImPlot::EndPlot();
    	}
    	ImGui::End();
	}
    {
        ImGui::Begin("Exercise 2");

        ImGui::Text("Filling a vector with %i objects", m_ArraySize);

        if (m_CalculateExercise2 == false)
            m_CalculateExercise2 = ImGui::Button("Trash the cache with GameObject3D");
        else
            ImGui::Text("Waiting for it...");

        if (m_ResultsNoPointer.empty() == false && ImPlot::BeginPlot("No Pointer"))
        {
            ImPlot::SetupAxis(ImAxis_X1, "step size", ImPlotAxisFlags_Lock);
            ImPlot::SetupAxis(ImAxis_Y1, "time in seconds", ImPlotAxisFlags_Lock);
            ImPlot::SetupAxisLimits(ImAxis_X1, 0.5, 10.5);
            ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 0.08);
            ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
        	ImPlot::SetupAxisTicks(ImAxis_X1, m_Ticks.data(), static_cast<int>(m_Ticks.size()), m_TimeSteps.data());
            ImPlot::PlotLine("no pointers", m_Ticks.data(), m_ResultsNoPointer.data(), static_cast<int>(m_Ticks.size()));
            ImPlot::EndPlot();
        }

        ImGui::Text("Filling a vector with %i objects containing pointers", m_ArraySize);

        if (m_CalculateExercise2Alt == false)
            m_CalculateExercise2Alt = ImGui::Button("Trash the cache with GameObject3DAlt");
        else
            ImGui::Text("Waiting for it...");

		if (m_ResultsWithPointer.empty() == false && ImPlot::BeginPlot("With Pointer"))
        {
            ImPlot::SetupAxis(ImAxis_X1, "step size", ImPlotAxisFlags_Lock);
            ImPlot::SetupAxis(ImAxis_Y1, "time in seconds", ImPlotAxisFlags_Lock);
            ImPlot::SetupAxisLimits(ImAxis_X1, 0.5, 10.5);
            ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 0.02);
            ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
            ImPlot::SetupAxisTicks(ImAxis_X1, m_Ticks.data(), static_cast<int>(m_Ticks.size()), m_TimeSteps.data());
			ImPlot::PlotLine("with pointers", m_Ticks.data(), m_ResultsWithPointer.data(), static_cast<int>(m_Ticks.size()));
            ImPlot::EndPlot();
        }

        if (m_ResultsWithPointer.empty() == false && m_ResultsNoPointer.empty() == false && ImPlot::BeginPlot("Combined"))
        {
            ImPlot::SetupAxis(ImAxis_X1, "step size", ImPlotAxisFlags_Lock);
            ImPlot::SetupAxis(ImAxis_Y1, "time in seconds", ImPlotAxisFlags_Lock);
            ImPlot::SetupAxisLimits(ImAxis_X1, 0.5, 10.5);
            ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 0.08);
            ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
            ImPlot::SetupAxisTicks(ImAxis_X1, m_Ticks.data(), static_cast<int>(m_Ticks.size()), m_TimeSteps.data());
            ImPlot::PlotLine("with pointers", m_Ticks.data(), m_ResultsWithPointer.data(), static_cast<int>(m_Ticks.size()));
            ImPlot::PlotLine("no pointers", m_Ticks.data(), m_ResultsNoPointer.data(), static_cast<int>(m_Ticks.size()));
            ImPlot::EndPlot();
        }

        ImGui::End();
    }
}

std::map<int, std::vector<float>> TrashTheCache::GatherData(bool outputValues) const
{
    std::vector<int> v;
    v.assign(m_ArraySize, 0);

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
                v[i] *= 2;
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

std::vector<double> TrashTheCache::AverageResult(std::map<int, std::vector<float>> data)
{
    std::vector<double> averages;

    for (auto& results : data | std::views::values)
    {
        // Sorting each 'results' vector in ascending order
        std::sort(results.begin(), results.end(), [](float a, float b)
            {
                return a < b;
            });

        float average = 0;
        for (int i = 1; i < static_cast<int>(results.size()) - 1; ++i)
        {
            average += results[i];
        }

        average /= (results.size() - 2);

        averages.push_back(average);
    }

    return averages;
}
