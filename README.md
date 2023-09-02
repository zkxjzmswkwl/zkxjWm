## Example config

```toml
[[window]]
substr = "Discord"
size = [2560, 1300]
center = true
borderless = false
minimizeAll = false

[[window]]
substr = "RuneScape"
size = [5000, 1250]
center = true
borderless = true
minimizeAll = true

[[hotkey]]
target = "RuneScape"
keycode = 36 # 36 = 0x24 = VK_HOME

[[hotkey]]
target = "Discord"
keycode = 49 # 43 = 0x31 = 1

[grow]
stepamount = 100 # amount to grow the window each step
keycode = 50 # 50 = 0x32 = 2
```