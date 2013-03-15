-- OLD TEST VERSION 
-- NEED TO BE PORTED TO WORK 

require("lusb")
print(lusb.version)

dofile("nxt_aux.lua")

--Find Nxt 
nxt_   = lusb.find_dev( nxt_usb.iVendor , nxt_usb.iProduct )
mouse_ = lusb.find_dev( 0x04f3 , 0x0210 )

print("claim nxt dev")
nxt   = claim_dev( nxt_   )
print("claim mouse dev")
mouse = claim_dev( mouse_ )

cal,x,y = 0,0,0

while true do
    out = mouse:interrupt_read(0x81, 4, 100000)
    cal = cal+1
    if out then
        xi,yi,b = string.byte( out , 2 , 4 )

        if (xi > 128 ) then xi = xi - 255 end
        if (yi > 128 ) then yi = yi - 255 end

        x = x+xi
        y = y+yi

        if cal > 10 then
            x=x/11
            y=y/11

            if (x < -5 ) then
                exec_cmd( nxt , left ) 
            elseif ( x > 5 ) then 
                exec_cmd( nxt , right ) 
            end

            if (y < -5) then
                exec_cmd( nxt , up ) 
            elseif (y > 5 ) then    
                exec_cmd( nxt , down ) 
            end
            cal,x,y = 0,0,0
        end

        if (b == 1 ) then
            exec_cmd( nxt , open ) 
        elseif ( b ==  255 ) then 
            exec_cmd( nxt , close ) 
        end

    end
end

