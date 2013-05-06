q1, q2:0->_,R
q1, reject: _,x -> R
q2, q2: x->R
q2, q3: 0 -> x,R
q2, accept: _->R
q3, q3: x->R
q3, q4: 0->R
q3, q5: _->L
q4, q3: 0->x,R
q4, q4: x->R
q4, reject: _->R
q5, q2: _-> R
q5, q5: 0,x->L