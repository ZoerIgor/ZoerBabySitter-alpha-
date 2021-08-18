#pragma once
#ifndef _DEBUG_
    #define _DEBUG_
    #include <Arduino.h>
    // Утечка памяти
	class MemoryLeak
	{
		public:
			MemoryLeak(String description);
			MemoryLeak(String description, int size);
			void add(int count);
			void add(int count, int size);
			void remove(int count);
			void remove(int count, int size);
			void getTotal();
		private:
			String _description;
			int _total, _size;
	};
#endif