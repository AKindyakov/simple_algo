//-------------------------------------------------------------------
// Sieve of Eratasthenes is a most simple algo for finding 
// all prime nubers up to any given limits.
// 
// akindyakov@gmail.com
//-------------------------------------------------------------------

//--- input data ----------------------------------------------------
hi_border = 150;
//-------------------------------------------------------------------

work_tab = ones(hi_border,1);

for i=2:hi_border,
   if work_tab(i) ~= 0 then
      j = i;
      while j*i <= hi_border,
         work_tab(i*j) = 0;
         j = j + 1;
      end
   end
end

for i=1:hi_border,
   if work_tab(i) ~= 0 then
      printf("%i ",i);
   end
end

//--- end of file ---------------------------------------------------
