#include "cpu_scheduler.h"


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
			currentProcess = wQ.Top();
			wQ.Pop();
			double delta;
			double curBurstT = currentProcess.GetBurstTime();

			if (wQ.GetAlgorithm() == Scheduling::SJF) {
				while (!pQ->empty()
					&& pQ->top().GetBurstTime() >= currentProcess.GetBurstTime()
					&& pQ->top().GetArrivalTime() - time <= curBurstT) {
					wQ.Push(pQ->top());
					pQ->pop();
				}
			}
			else { //Priority
				while (!pQ->empty()
					&& pQ->top().GetPriority() >= currentProcess.GetPriority()
					&& pQ->top().GetArrivalTime() - time <= curBurstT) {
					wQ.Push(pQ->top());
					pQ->pop();
				}
			}

			if (pQ->empty() || pQ->top().GetArrivalTime() - time > currentProcess.GetBurstTime()) {
				delta = currentProcess.GetBurstTime();
			}
			else {
				delta = pQ->top().GetArrivalTime() - time;
				wQ.Push(currentProcess - delta);
			}
			
			time += delta;
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