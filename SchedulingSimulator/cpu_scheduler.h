#pragma once
#include "waiting_queue.h"


class CpuScheduler
{
public:
	CpuScheduler() : time(0), isRunning(false), isPreemptive(false), isRoundRobin(false) {}
	void SetProcessQueue(std::unique_ptr<ProcessQueue> pQ)
		{ this->pQ = std::move(pQ); }
	void SetAlgorithm(Scheduling wQalgorithm, bool isPreemptive, bool isRoundRobin)
		{ wQ.SetAlgorithm(wQalgorithm); this->isPreemptive = isPreemptive; this->isRoundRobin = isRoundRobin; }

	const waitingQueue& GetWQhandler() const
		{ return wQ; }
	const GanttChart& GetGantthandler() const
		{ return ganttChart; }
	bool Empty() const
		{ return ganttChart.empty(); }
	bool IsRunning() const
		{ return isRunning; }

	void StepForward();
	void Reset();

private:
	std::unique_ptr<ProcessQueue> pQ;
	waitingQueue wQ;
	GanttChart ganttChart;
	Process currentProcess;
	double time;

	bool isPreemptive;
	bool isRoundRobin;
	bool isRunning;
};



void CpuScheduler::StepForward()
{
	// CPU scheduler �ʱ�ȭ
	if (!isRunning) {

		if (!pQ)
			return;
		wQ.Clear();
		ganttChart.clear();
		time = 0;
		isRunning = true;
	}

	// ���� �ð� ���� ������ ���μ������� processQueue���� waitingQueue�� �̵�
	while (!pQ->empty() && time >= pQ->top().GetArrivalTime()) {

		wQ.Push(pQ->top());
		pQ->pop();
	}

	// Dispatch process from waitingQueue to CPU
	if (!wQ.Empty()) {

		// Preemptive
		if (isPreemptive) {

			// 
			//
			// 
			//
			//
			//
		}

		// Round-Robin
		else if (isRoundRobin) {

			//
			//
			// 
			//
			//
			//
		}

		// Non-preemptive and no time-quantum
		else {

			currentProcess = wQ.Top();
			time += currentProcess.GetBurstTime();
			wQ.Pop();
		}
	}
	// If waitingQueue is empty, empty process
	else {

		currentProcess.SetPid("");
		time = pQ->top().GetArrivalTime();
	}

	// ganttChart�� ���
	ganttChart.emplace_back(currentProcess.GetPid(), time);
	// scheduling ���� ����
	if (pQ->empty() && wQ.Empty()) {

		isRunning = false;
		pQ = nullptr;
	}
}

void CpuScheduler::Reset()
{
	isRunning = false;
	pQ = nullptr;
	wQ.Clear();
	ganttChart.clear();
}