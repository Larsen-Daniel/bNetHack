-- NetHack nhlib.lua	$NHDT-Date: 1652196140 2022/05/10 15:22:20 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.4 $
--	Copyright (c) 2021 by Pasi Kallinen
-- NetHack may be freely redistributed.  See license for details.
-- compatibility shim
math.random = function(...)
   local arg = {...};
   if (#arg == 1) then
      return 1 + nh.rn2(arg[1]);
   elseif (#arg == 2) then
      return nh.random(arg[1], arg[2] + 1 - arg[1]);
   else
      -- we don't support reals
      error("NetHack math.random requires at least one parameter");
   end
end

function shuffle(list)
   for i = #list, 2, -1 do
      local j = math.random(i)
      list[i], list[j] = list[j], list[i]
   end
end

align = { "law", "neutral", "chaos" };
shuffle(align);

-- d(2,6) = 2d6
-- d(20) = 1d20 (single argument = implicit 1 die)
function d(dice, faces)
   if (faces == nil) then
      -- 1-arg form: argument "dice" is actually the number of faces
      return math.random(1, dice)
   else
      local sum = 0
      for i=1,dice do
         sum = sum + math.random(1, faces)
      end
      return sum
   end
end

-- percent(20) returns true 20% of the time
function percent(threshold)
   return math.random(0, 99) < threshold
end

function monkfoodshop()
   if (u.role == "Monk") then
      return "health food shop";
   end
   return "food shop";
end

-- tweaks to gehennom levels; might add random lava pools or
-- a lava river.
-- protected_area is a selection where no changes will be done.
function hell_tweaks(protected_area)
   local liquid = "L";
   local ground = ".";
   local n_prot = protected_area:numpoints();
   local prot = protected_area:negate();

   -- random pools
   if (percent(20 + u.depth)) then
      local pools = selection.new();
      local maxpools = 5 + math.random(u.depth);
      for i = 1, maxpools do
         pools:set();
      end
      pools = pools | selection.grow(selection.set(selection.new()), "west")
      pools = pools | selection.grow(selection.set(selection.new()), "north")
      pools = pools | selection.grow(selection.set(selection.new()), "random")

      pools = pools & prot;

      if (percent(80)) then
         local poolground = pools:clone():grow("all") & prot;
         local pval = math.random(1, 8) * 10;
         des.terrain(poolground:percentage(pval), ground)
      end
      des.terrain(pools, liquid)
   end

   -- river
   if (percent(50)) then
      local allrivers = selection.new();
      local reqpts = ((nhc.COLNO * nhc.ROWNO) - n_prot) / 12; -- # of lava pools required
      local rpts = 0;
      local rivertries = 0;

      repeat
            local floor = selection.match(ground);
            local a = selection.rndcoord(floor);
            local b = selection.rndcoord(floor);
            local lavariver = selection.randline(selection.new(), a.x, a.y, b.x, b.y, 10);

            if (percent(50)) then
               lavariver = selection.grow(lavariver, "north");
            end
            if (percent(50)) then
               lavariver = selection.grow(lavariver, "west");
            end
            allrivers = allrivers | lavariver;
            allrivers = allrivers & prot;

            rpts = allrivers:numpoints();
            rivertries = rivertries + 1;
      until ((rpts > reqpts) or (rivertries > 7));

      if (percent(60)) then
         local prc = 10 * math.random(1, 6);
         local riverbanks = selection.grow(allrivers);
         riverbanks = riverbanks & prot;
         des.terrain(selection.percentage(riverbanks, prc), ground);
      end

      des.terrain(allrivers, liquid);
   end

   -- replacing some walls with boulders
   if (percent(20)) then
      local amount = 3 * math.random(1, 8);
      local bwalls = selection.match([[.w.]]):percentage(amount) | selection.match(".\nw\n."):percentage(amount);
      bwalls = bwalls & prot;
      bwalls:iterate(function (x,y)
            des.terrain(x, y, ".");
            des.object("boulder", x, y);
      end);
   end

   -- replacing some walls with iron bars
   if (percent(20)) then
      local amount = 3 * math.random(1, 8);
      local fwalls = selection.match([[.w.]]):percentage(amount) | selection.match(".\nw\n."):percentage(amount);
      fwalls = fwalls:grow() & selection.match("w") & prot;
      des.terrain(fwalls, "F");
   end

end

-- pline with variable number of arguments
function pline(fmt, ...)
   nh.pline(string.format(fmt, table.unpack({...})));
end
