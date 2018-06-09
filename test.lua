package.cpath = package.cpath .. ";./target/?.so"
local codp = require("codp")
print(codp.sin(3.1415/2))
local core = codp.newcore(6)
codp.coreput(
  core,
  2, {
    opcode = 9,
    mode = 6,
    a = {
      mode = 3,
      number = 7
    },
    b = {
      mode = 0,
      number = 5
    }
})
codp.coreput(
  core,
  0, {
    opcode = 06,
    mode = 2,
    a = {
      mode = 1,
      number = 6
    },
    b = {
      mode = 2,
      number = 4
    }
})
codp.coreprint(core)
