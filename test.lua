package.cpath = package.cpath .. ";./target/?.so"
local codp = require("codp")
print(codp.sin(3.1415/2))
local core = codp.newcore(6)
core:put(
  2,
  {
    opcode = 9,
    modifier = 6,
    a = {
      mode = 3,
      number = 7
    },
    b = {
      mode = 0,
      number = 5
    }
})
core:put(
  0,
  {
    opcode = 06,
    modifier = 2,
    a = {
      mode = 1,
      number = 6
    },
    b = {
      mode = 2,
      number = 4
    }
})
core:print()
