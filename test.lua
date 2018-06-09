package.cpath = package.cpath .. ";./target/?.so"
local codp = require("codp")
print(codp.sin(3.1415/2))
print(codp.newcore(1))
codp.printinstruction({
    opcode = 1,
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

print("")
