#include "utils/DataContainer.h"
#include "arithmetic_encoding_h/FrequencyContainer.h"
#include "arithmetic_encoding_h/ArithmeticEncoder.h"
#include "arithmetic_encoding_h/ArithmeticDecoder.h"

using namespace std;

int main(int argc, char* argv[])
{
	DataContainer* d = new DataContainer(argv[1]);
	FrequencyContainer* f = new FrequencyContainer();
	f->computeFrequencies(d);

	ArithmeticEncoder* ae = new ArithmeticEncoder(argv[2], ',');
	f->accept(ae);
	ae->printCode();

	ArithmeticDecoder* ad = new ArithmeticDecoder(ae->getCode());
	f->accept(ad);
	ad->printSymbols();

	delete d;
	delete f;
	delete ae;
	delete ad;

	return 0;
}