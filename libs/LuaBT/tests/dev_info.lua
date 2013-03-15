require("table_print")
require("luabt")


res,err = luabt.dev_info(0)

if res then
    table_print(res)
else
    print(err)
end
