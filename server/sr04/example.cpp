#include "SR04.hpp"
#include <csignal>
#include <definitions.hpp>

size_t numOfMeasurements = 0;
size_t numOfFailures = 0;
void finaliser(int sig)
{
	pr_dbg("sig:", sig);
	pr_dbg("probability of failure:%f", static_cast<float>(numOfFailures) / numOfMeasurements);
	exit(0);

}


int main(int argc, char** argv)
{
	struct sigaction sigact;
	sigact.sa_handler = finaliser;
	sigaction(SIGINT, &sigact, NULL);
	wiringPiSetup();
	SR04 sonar(4,5);
	while(1)
	{
		float dist = sonar.distance(std::stoi(argv[1]));
		numOfMeasurements++;
		if(dist < 0)
			numOfFailures++;
		fprintf(stderr, "distance: %f\n", dist);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}