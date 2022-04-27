local expedition_name = "The Agents of Evil"
local expedition_info = {
	expedition = { name=expedition_name, min_players=1, max_players=1 },
	instance   = { zone="mira", version=1, duration=eq.seconds("24h") },
	compass    = { zone="nexus", x=-44.45, y=-20.11, z=313 },
	safereturn = { zone="nexus", x=0, y=0, z=-30.87, h=313 },
	zonein     = { x=650, y=558, z=-90.87, h=500 }
}

function event_say(e)
	if(e.message:findi("hail")) then
		e.self:Say("Hail, friend. I am Commander Ahkina Vri, tasked with hunting down and destroying the Agents of Evil.  I take it you've [spoken with my commander]?");
	elseif(e.message:findi("spoken with my commander")) then
		e.self:Say("Good, she has a stout heart.  I would not trust anyone else at the head of our Order.  You look liek you have a good heart too.  Would you be willing to assist my order in [rooting out evil]?");
	elseif(e.message:findi("rooting out evil")) then
		if(e.other:GetLevel() < 50) then
			e.self:Say("While I do not doubt your heart, I do not want the guilt of your death on my soul.  When you become strong enough to assist the Legion, return to me.");
		else
			e.self:Say("I thought you'd be interested.  Using the power of the Nexus, I can send you to root out the evil.  Do you [accept]?.");
		end
    elseif(e.message:findi("accept")) then
        local haslockout = e.other:HasExpeditionLockout(expedition_name, "Daily Reset")
        local dz= e.other:GetExpedition()
        if haslockout then
                e.self:Say("You have already accepted this task today.")
        elseif(e.other:GetLevel() > 49) then
            if(dz.valid and dz.GetName() == expedition_name) then
                e.self:Say("You only need to let me know when you are [ready].")
            else
                local dz = e.other:CreateExpedition(expedition_info)
                if(dz.valid) then
                    e.other:AddExpeditionLockout(expedition_name, "Daily Reset", 86400)
                    e.self:Say("Excellent!  Let me know when you are [ready] to enter and I will facilitate your transportation.")
                end
            end    
        end
	elseif(e.message:findi("ready")) then
       e.self:Say("Bring honor to the Legion!")
       e.other:MovePCDynamicZone("mira")
    end
end
