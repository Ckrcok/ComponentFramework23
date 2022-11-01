#ifndef TIMER_H
#define TIMER_H
#include <SDL.h>


class Timer {
public:
	Timer();
	~Timer();

	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;

	void Start();
	void UpdateFrameTicks();
	float GetDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_) const;
	float GetCurrentTicks() const;
	static SDL_TimerID SetSingleEvent(Uint32 interval, void* param);
	
	unsigned int prevTicks;
	unsigned int currentTicks;
	struct SingleEventData {
		void* param;
		Uint32 eventID;
	};
	static Uint32 callbackfunc(Uint32 interval, void* singleEventParam);
	

};


#endif
