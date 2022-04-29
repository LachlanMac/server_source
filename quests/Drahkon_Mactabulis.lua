function event_say(e)
	if(e.message:findi("hail")) then
        e.self:Say("Greetings.  I am sorry but I am too busy to talk right now.  I am currently saddled with the logistics of transporting our weaponsmith here who will be able to fashion weapons of epic proportion using treasures obtained from the lairs of evil spread out around the world.  Come back next week and I may have something for you.");
    end
end