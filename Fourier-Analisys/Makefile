.PHONY: clean

%.exe: %.cpp
	@g++ -g $< -o $@

sinusoidal_signal: SinusoidalSignalGenerator.exe 
	@./$< sin1.wav 400 15000
	@./$< sin2.wav 1000 10000

combine_signals: SignalCombine.exe sinusoidal_signal
	@./$< sin1.wav sin2.wav sin3.wav

frequency_charts: FourierMagnitude.exe combine_signals
	@./$< sin1.wav
	@./$< sin2.wav
	@./$< sin3.wav
	
	@python3 ./plot.py sin1.wav sin2.wav sin3.wav

analyze_frequency: FrequencyAnalize.exe combine_signals
	@./$< sin3.wav 400 1000

two_way_fourier: TwoWayFourier.exe combine_signals
	@./$< sin3.wav

clean:
	rm -f output/*
	rm -f audio/*
	rm -f *.exe