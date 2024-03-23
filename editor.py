import sys
import tty
import termios
import os
import time

MAX_ROWS = 100
MAX_COLS = 100
buffer = [""] * MAX_ROWS

def init_termios():
    old_termios = termios.tcgetattr(sys.stdin)
    new_termios = termios.tcgetattr(sys.stdin)
    new_termios[3] = new_termios[3] & ~termios.ICANON & ~termios.ECHO
    termios.tcsetattr(sys.stdin, termios.TCSANOW, new_termios)
    return old_termios

def reset_termios(old_termios):
    termios.tcsetattr(sys.stdin, termios.TCSANOW, old_termios)

def move_cursor_left(cursor_row, cursor_col):
    if cursor_col > 0:
        sys.stdout.write("\033[D")
        cursor_col -= 1
    return cursor_col

def move_cursor_right(cursor_row, cursor_col):
    if cursor_col < MAX_COLS - 1:
        sys.stdout.write("\033[C")
        cursor_col += 1
    return cursor_col

def move_cursor_up(cursor_row, cursor_col):
    if cursor_row > 0:
        sys.stdout.write("\033[A")
        cursor_row -= 1
    return cursor_row

def move_cursor_down(cursor_row, cursor_col):
    if cursor_row < MAX_ROWS - 1:
        sys.stdout.write("\033[B")
        cursor_row += 1
    return cursor_row

def move_cursor_next(cursor_row, cursor_col):
    if cursor_row < MAX_ROWS - 1:
        cursor_row += 1
        cursor_col = 0
    return cursor_row, cursor_col

def delete_character(text, cursor_row, cursor_col):
    if cursor_col > 0:
        cursor_col = move_cursor_left(cursor_row, cursor_col)
        text[cursor_row] = text[cursor_row][:cursor_col] + text[cursor_row][cursor_col+1:] + " "
        sys.stdout.write("\033[P")
    return cursor_col

def print_character(cursor_row, cursor_col, c):
    if c == 20:
        sys.stdout.write("✔")
    elif c == 24:
        sys.stdout.write("X")
    else:
        sys.stdout.write(chr(c))

def special_character(cursor_row, cursor_col, c):
    with open("Test/keyboard.txt", "w") as file:
        file.write(chr(c))
    time.sleep(0.1)
    with open("Test/keyboard.txt", "r") as file:
        s = file.read()
        sys.stdout.write(s)
    os.remove("Test/keyboard.txt")

def insert_character(text, cursor_row, cursor_col, c, print_flag):
    if cursor_col < MAX_COLS:
        if c == ord('\n'):
            valid = False
            for i in range(MAX_COLS - 2, -1, -1):
                if text[cursor_row][i] == '\n':
                    valid = True
                    break
                elif text[cursor_row][i] != '\0':
                    text[cursor_row] = text[cursor_row][:i+1] + '\n'
                    valid = True
                    break
            if not valid:
                text[cursor_row] = '\n' + text[cursor_row]
            if not print_flag:
                special_character(cursor_row, cursor_col, c)
            else:
                print_character(cursor_row, cursor_col, c)
            cursor_row, cursor_col = move_cursor_next(cursor_row, cursor_col)
        else:
            text[cursor_row] = text[cursor_row][:cursor_col] + chr(c) + text[cursor_row][cursor_col:]
            if not print_flag:
                special_character(cursor_row, cursor_col, c)
            else:
                print_character(cursor_row, cursor_col, c)
            if cursor_col == MAX_COLS:
                cursor_row, cursor_col = move_cursor_next(cursor_row, cursor_col)
            else:
                cursor_col += 1
    return cursor_row, cursor_col

def save_character(c, file):
    if c != '\0':
        file.write(c)

def main():
    old_termios = init_termios()
    text = ['\0' * MAX_COLS for _ in range(MAX_ROWS)]
    cursor_row, cursor_col = 0, 0

    if len(sys.argv) != 2:
        sys.stderr.write("Usage: {} <filename>\n".format(sys.argv[0]))
        sys.exit(1)

    filename = sys.argv[1]

    try:
        with open("editor.txt", "r") as file:
            for line in file:
                for char in line:
                    cursor_row, cursor_col = insert_character(text, cursor_row, cursor_col, ord(char), True)
    except IOError:
        sys.stderr.write("Error opening file {}\n".format(filename))
        sys.exit(1)

    try:
        while True:
            c = sys.stdin.read(1)

            if ord(c) == 4:  # Ctrl+D
                with open("editor.txt", "w") as file:
                    for line in text:
                        for char in line:
                            save_character(char, file)
                break

            elif ord(c) == 2:  # Copy button
                if cursor_col == 0:
                    buffer[:] = text[cursor_row]

            elif ord(c) == 22:  # Paste button
                if cursor_col == 0:
                    for char in buffer:
                        if char != '\n':
                            cursor_row, cursor_col = insert_character(text, cursor_row, cursor_col, ord(char), True)
                        else:
                            break

            elif ord(c) == 27:  # Escape key for cursor movement
                next_c = sys.stdin.read(1)
                if next_c == '[':
                    movement = sys.stdin.read(1)
                    if movement == 'A':  # Up arrow key
                        cursor_row = move_cursor_up(cursor_row, cursor_col)
                    elif movement == 'B':  # Down arrow key
                        cursor_row = move_cursor_down(cursor_row, cursor_col)
                    elif movement == 'C':  # Right arrow key
                        cursor_col = move_cursor_right(cursor_row, cursor_col)
                    elif movement == 'D':  # Left arrow key
                        cursor_col = move_cursor_left(cursor_row, cursor_col)

            elif ord(c) == 127:  # Backspace key
                cursor_col = delete_character(text, cursor_row, cursor_col)

            else:
                cursor_row, cursor_col = insert_character(text, cursor_row, cursor_col, ord(c), False)

    finally:
        reset_termios(old_termios)
        sys.stdout.write("\nChanges saved to {}\n".format(filename))

main()
