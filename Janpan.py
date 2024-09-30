import tkinter as tk
import random

# Lists of Hiragana and Katakana characters
hiragana = [
    'あ', 'い', 'う', 'え', 'お',
    'か', 'き', 'く', 'け', 'こ',
    'さ', 'し', 'す', 'せ', 'そ',
    'た', 'ち', 'つ', 'て', 'と',
    'な', 'に', 'ぬ', 'ね', 'の',
    'は', 'ひ', 'ふ', 'へ', 'ほ',
    'ま', 'み', 'む', 'め', 'も',
    'や', 'ゆ', 'よ',
    'ら', 'り', 'る', 'れ', 'ろ',
    'わ', 'を', 'ん'
]

katakana = [
    'ア', 'イ', 'ウ', 'エ', 'オ',
    'カ', 'キ', 'ク', 'ケ', 'コ',
    'サ', 'シ', 'ス', 'セ', 'ソ',
    'タ', 'チ', 'ツ', 'テ', 'ト',
    'ナ', 'ニ', 'ヌ', 'ネ', 'ノ',
    'ハ', 'ヒ', 'フ', 'ヘ', 'ホ',
    'マ', 'ミ', 'ム', 'メ', 'モ',
    'ヤ', 'ユ', 'ヨ',
    'ラ', 'リ', 'ル', 'レ', 'ロ',
    'ワ', 'ヲ', 'ン'
]

def show_random_character(char_set):
    random_char = random.choice(char_set)
    label.config(text=random_char)

# Set up the main application window
root = tk.Tk()
root.title("Random Kana Generator")
root.geometry("400x300")
root.resizable(False, False)
root.configure(bg="#f0f8ff")

# Create a label to display the Kana character
label = tk.Label(root, text="", font=("Arial", 100), padx=20, pady=20, bg="#f0f8ff", fg="#2e8b57")
label.pack()

# Create buttons for generating random Hiragana and Katakana
hiragana_button = tk.Button(
    root, text="Random Hiragana", command=lambda: show_random_character(hiragana),
    font=("Arial", 16), bg="#ffefd5", fg="#8b0000", activebackground="#ffa07a"
)
hiragana_button.pack(side=tk.LEFT, expand=True, fill=tk.BOTH)

katakana_button = tk.Button(
    root, text="Random Katakana", command=lambda: show_random_character(katakana),
    font=("Arial", 16), bg="#ffefd5", fg="#8b0000", activebackground="#ffa07a"
)
katakana_button.pack(side=tk.RIGHT, expand=True, fill=tk.BOTH)

# Run the application
root.mainloop()