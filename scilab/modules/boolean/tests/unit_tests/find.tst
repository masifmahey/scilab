// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) - 2015 - Scilab Enterprises - Calixte DENIZET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
//

a = zeros(1,2000);
a(1:2:2000)=1:1000;

assert_checkequal(and(find(a==0)==(2:2:2000)), %T);