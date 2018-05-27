package.cpath = package.cpath .. ";./target/?.so"
local codp = require("codp")
print(codp.sin(3.1415/2))
