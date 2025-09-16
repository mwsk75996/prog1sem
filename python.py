import tkinter as tk
import keyboard
from pynput.keyboard import Controller as KeyController
from pynput.mouse import Controller as MouseController, Button

# Controllers for real key/mouse input
kb = KeyController()
ms = MouseController()

# Actions and their states
actions = {
    'W': False,
    'A': False,
    'S': False,
    'D': False,
    'M1': False,
    'Stop': False
}
labels = {}

# Map scan codes → actions (based on what you gave me)
# Note: I've removed the invalid `4F` literal. If you want Stop bound to a specific key,
# add it here as the correct scan code or key name.
scan_map = {
    72: "W",   # numpad 8
    75: "A",   # numpad 4
    80: "S",   # numpad 2
    77: "D",   # numpad 6
    76: "M1",  # numpad 5
}

def set_label(action):
    labels[action].config(bg='green' if actions[action] else 'red')

def do_toggle(action):
    """Toggle a single action on/off and press/release the real key/mouse."""
    actions[action] = not actions[action]
    set_label(action)
    
    if action in ['W','A','S','D']:
        key = action.lower()
        if actions[action]:
            kb.press(key)
        else:
            try:
                kb.release(key)
            except Exception:
                pass
    elif action == 'M1':
        if actions[action]:
            ms.press(Button.left)
        else:
            try:
                ms.release(Button.left)
            except Exception:
                pass

def hotkey_handler(action):
    # Ensure GUI updates happen on the Tk main thread
    root.after(0, lambda: do_toggle(action))

def failsafe_all_off():
    """Failsafe: release everything and set all actions False.
       Bound to Numpad1 (End) as requested."""
    any_changed = False
    for action, state in list(actions.items()):
        if state:
            any_changed = True
            # release real inputs if they are active
            if action in ['W','A','S','D']:
                try:
                    kb.release(action.lower())
                except Exception:
                    pass
            elif action == 'M1':
                try:
                    ms.release(Button.left)
                except Exception:
                    pass
            actions[action] = False

    # update all labels on the GUI
    for a in actions:
        set_label(a)

    if any_changed:
        print("Failsafe (End): all actions turned OFF")
    else:
        print("Failsafe (End) pressed — no active actions to turn off")

# GUI setup
root = tk.Tk()
root.title("Key Toggler (WASD + M1) - with Failsafe")
root.geometry("250x300")

for action in actions:
    lbl = tk.Label(root, text=action, width=20, height=2,
                   bg='red', fg='white', font=('Arial', 12))
    lbl.pack(pady=5)
    lbl.bind("<Button-1>", lambda ev, a=action: do_toggle(a))
    labels[action] = lbl

# Bind scan codes (existing behavior)
for sc, action in scan_map.items():
    # bind the scan code to toggle its action
    keyboard.on_press_key(sc, lambda e, a=action: hotkey_handler(a))
    print(f"Bound scan code {sc} -> {action}")

# Bind the failsafe to the End key (Numpad 1 when NumLock is off)
# Using the key name 'end' is more portable than raw scan codes in many setups.
keyboard.on_press_key('end', lambda e: root.after(0, failsafe_all_off))
print("Bound 'end' (Numpad 1/End) -> failsafe_all_off")

def on_close():
    # release any held inputs before exit
    for action, state in actions.items():
        if state:
            if action in ['W','A','S','D']:
                try:
                    kb.release(action.lower())
                except Exception:
                    pass
            elif action == 'M1':
                try:
                    ms.release(Button.left)
                except Exception:
                    pass
    root.destroy()

root.protocol("WM_DELETE_WINDOW", on_close)
root.mainloop()