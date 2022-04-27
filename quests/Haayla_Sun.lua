function event_say(e)
    if(e.message:findi("hail")) then
            e.self:Say("Greetings.  I am Haayla Sun from the Legion of Vri.  My compatriots and I are are looking to explore the deepest chambers of Norrath in search of [untold treasures].");
    elseif(e.message:findi("untold treasures")) then
            e.self:Say("Yes. Although [tokens of the enemy] would be a better way to describe them.  Agents of evil are everywhere and obtaining these markers from their cold, dead hands is the only way to ensure ou>
    elseif(e.message:findi("tokens of the enemy")) then
            if(e.other:GetLevel() < 50) then
                    e.self:Say("While there is a lot of evil in this world, I do not think you are quite ready for such a task.  Have a word with my fellow Legion members Ahkina and Drahkon when you gain some more e>
            else
                    e.self:Say("Maybe you can help?  Speak with my fellow Legion members Ahkina and Drahkon to see what you can do to help us on our quest.");
            end
    end
end
                                                                                                  
function event_say(e)
    if(e.message:findi("hail")) then
            e.self:Say("Hail, friend. I am Commander Ahkina Vri, tasked with hunting down and destroying the Agents of Evil.  I take it you've [spoken with my commander]?")
    elseif(e.message:findi("spoken with my commander")) then
            e.self:Say("Good, she has a stout heart.  I would not trust anyone else at the head of our Order.  You look liek you have a good heart too.  Would you be willing to assist my order in [rooting out evil]?")
    elseif(e.message:findi("rooting out evil")) then
            if(e.other:GetLevel() < 50) then
                e.self:Say("While I do not doubt your heart, I do not want the guilt of your death on my soul.  When you become strong enough to assist the Legion, return to me.")
            else
                e.self:Say("I thought you'd be interested.  Using the power of the Nexus, I can send you to root out the evil.  Do you [accept]?.")
            end
    else if(e.message:findi("[accept]")) then
            if(e.other:GetLevel() > 49)
                e.self:Say("Good.  Here are the details.  Serve the Legion well.")
            end
    elseif(e.message:findi("ready")) then
            e.self:Say("Ok")
    end
end