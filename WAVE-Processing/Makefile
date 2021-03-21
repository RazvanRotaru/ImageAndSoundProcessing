.PHONY: encode decode extract create histogram compare_extracted clean

encode:
	g++ -g MuLawEncoder.cpp -o MuLawEncoder.exe
	./MuLawEncoder.exe $(file)
decode:
	g++ -g MuLawDecoder.cpp -o MuLawDecoder.exe
	./MuLawDecoder.exe $(file)
	
extract:
	g++ -g WaveParser.cpp -o WaveParser.exe
	./WaveParser.exe $(file)

compare_extracted:
	@diff --strip-trailing-cr output/normalized_sample_values.txt ref/sample-data.txt \
										&& echo "Files are identical" || echo "Files differ" /
	
create:
	g++ -g WaveCreator.cpp -o WaveCreator.exe
	./WaveCreator.exe $(duration)

histogram:
	g++ -g Histogram.cpp -o Histogram.exe
	./Histogram.exe $(file)
	python3 plotHistogram.py output/histogram_values.csv

clean:
	rm -f output/*
	rm -f *.exe
	rm -f audio/my* audio/beep1.wav audio/beep2.wav