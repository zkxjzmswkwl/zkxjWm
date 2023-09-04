## Example config

```toml
# Default and currently unchangable mod key is ALT.

[[window]]
substr = "Discord"
size = [2560, 1300]
center = true
borderless = false
minimizeAll = false
keycode = 49     # 0x31 (1)

[[window]]
substr = "RuneScape"
size = [1500, 1000]
center = false
borderless = false 
minimizeAll = true 
keycode = 54     # 0x36 (6)

# Holding shift will shrink the window, not will grow it.
[grow]
stepamount = 300 # amount to grow or shrink the window by each step
keycode = 50     # 0x32 (2)
```
