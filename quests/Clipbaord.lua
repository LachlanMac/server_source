function event_say(e)
	if(e.message:findi("hail")) then
		e.self:Say("Hail, friend. I am Commander Ahkina Vri, tasked with hunting down and destroying the Agents of Evil.  I take it you have [spoken with my commander]?");
	elseif(e.message:findi("spoken with my commander")) then
		e.self:Say("Good, she has a stout heart.  I would not trust anyone else at the head of our Order.  You look like you have a good heart, too.  Would you be willing to assist my order in [rooting out evil]?");
	elseif(e.message:findi("rooting out evil")) then
		if(e.other:GetLevel() < 50) then
			e.self:Say("While I do not doubt your heart, I do not want the guilt of your death on my soul.  When you become strong enough to assist the Legion, return to me.");
		else
			e.self:Say("I thought you would be interested.  Using the power of the Nexus, I can send you to root out the evil.  Do you [accept]?.");
		end
    else if(e.message:findi("[accept]")) then
        if(e.other:GetLevel() < 50) then
			e.self:Say("Come back when you have more experience.");
		else
			e.self:Say("I thought you would be interested.  Using the power of the Nexus, I can send you to root out the evil.  Do you [accept]?.");
		end
    elseif(e.message:findi("ready")) then
        e.self:Say("Ok.");
    end
end