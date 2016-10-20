#include <cstdlib>
#include <ctime>



class Random
{
	private:
		long seed;
		long genCount;
	
	public:
		Random();
		Random(long seed);
		~Random();

		int nextInt();
		int nextInt(int min, int max);

		int getSeed();
		int getGenCount();
};
