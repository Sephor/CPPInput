import random
import subprocess
import time
import math
import filecmp

INPUT = 'input'
CPP_FILE = 'parsers.cpp'
PROGRAM = 'build/Release/numberparsing'
SAMPLESIZE = 100
OUT_PREFIX = 'out_'

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
    times = []
    with open(INPUT, 'r') as input_file:
        start_time = time.time()
        process = subprocess.Popen(PROGRAM, stdin=input_file,
            stdout=subprocess.PIPE)
        process.wait()
        for line in process.stdout:
            if len(line) == 0:
                continue
            output = line.decode('utf-8').rstrip('\r\n')
            name_and_time = output.split(':')
            times.append((name_and_time[0], int(name_and_time[1])))
    return times

def calculate_average_and_sd(times):
    average = sum(times) / len(times)
    square_deviations = [(t - average) ** 2 for t in times]
    sd = math.sqrt(sum(square_deviations) / len(times))
    return (average, sd)

def calculate_results(times):
    sorted_times = {}
    for name, time in times:
        if name in sorted_times:
            sorted_times[name].append(time)
        else:
            sorted_times[name] = [time]
    result = {}
    for name in sorted_times:
        result[name] = calculate_average_and_sd(sorted_times[name])
    return result

def compare_file_to_input(name):
    with open(INPUT, 'r') as in_file, open(OUT_PREFIX + name, 'r') as out_file:
        if in_file.readline().rstrip('\r\n') != out_file.readline().rstrip('\r\n'):
            return False
    return True

def verify_results(names):
    result = {}
    for name in names:
        result[name] = compare_file_to_input(name)
    return result

def main():
    times = []
    random.seed(0)
    max_numbers, max_digits = read_input_length()
    print('Creating input file ({} numbers, {} digits each).'.format(
        max_numbers, max_digits))
    create_input(max_numbers, max_digits)
    for i in range(SAMPLESIZE):
        print(' ' * 20, end='\r')
        print('Run {}/{}'.format(i + 1, SAMPLESIZE), end='\r')
        times.extend(time_program())
    print()
    results = calculate_results(times)
    correct = verify_results(results.keys())
    print(correct)

if __name__ == '__main__':
    main()
