import random
import subprocess
import time
import math

INPUT = 'input'
CPP_FILE = 'parsers.cpp'
PROGRAM = 'build/Release/numberparsing'
SAMPLESIZE = 100

def create_input(max_numbers, max_digits):
    with open(INPUT, 'w', newline='\n') as input_file:
        input_file.write(str(max_numbers) + '\n')
        progress_step = max_numbers / 100
        for i in range(max_numbers):
            if i % progress_step == 0:
                print(' ' * 20, end='\r')
                print('Progress: {:.0f}%'.format(i / max_numbers * 100), end='\r')
            input_file.write(
                str(random.randint(0, 10 ** max_digits - 1)) + '\n')
        print('Progress: {:.0f}%'.format(100))

def read_input_length():
    with open(CPP_FILE, 'r') as cpp_file:
        cpp_file.readline()
        max_numbers = int(cpp_file.readline()[len('#define MAXNUMBERS '):-1])
        max_digits = int(cpp_file.readline()[len('#define MAXDIGITS '):-1]) - 1
    return (max_numbers, max_digits)

def time_program():
    start_time = 0
    end_time = 0
    with open(INPUT, 'r') as input_file:
        start_time = time.time()
        process = subprocess.Popen(PROGRAM, stdin=input_file)
        process.wait()
        end_time = time.time()
    return (end_time - start_time) * 1000

def main():
    random.seed(0)
    max_numbers, max_digits = read_input_length()
    print('Creating input file ({} numbers, {} digits each).'.format(
        max_numbers, max_digits))
    create_input(max_numbers, max_digits)
    times = []
    for i in range(SAMPLESIZE):
        print(' ' * 20, end='\r')
        print('Run {}/{}'.format(i + 1, SAMPLESIZE), end='\r')
        times.append(time_program())
    print()
    average_time = sum(times) / len(times)
    absolute_deviations = [abs(t - average_time) for t in times]
    average_absolute_deviation = (sum(absolute_deviations) / len(times))
    deviation_percentage = average_absolute_deviation / average_time * 100
    standard_deviation = sum([d ** 2 for d in absolute_deviations]) / len(times)
    standard_deviation = math.sqrt(standard_deviation)
    print('avg: {:.2f}ms'.format(average_time))
    print('avg abs. deviation: {:.2f}ms ({:.2f}%)'.format(
        average_absolute_deviation, deviation_percentage))
    print('SD: {:.2f}ms'.format(standard_deviation))

if __name__ == '__main__':
    main()
