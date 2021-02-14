import time


class Timer:
    _start_time = None
    @classmethod
    def start_measure(cls):
        cls._start_time = time.perf_counter()

    @classmethod
    def get_time(cls):
        return time.perf_counter() - cls._start_time

    @classmethod
    def print_time_elapsed(cls):
        print('Time elapsed: {:.3f} s'.format(cls.get_time()))
