# FallingBall

An object falling on a foot : we suppose that the object's size doesn't change ( so just the density ), we get a scream when the dude feels the pain .

Just for fun.

We will test some ideas on the physics and biology ( pain )

---
1. Variables

Object : weight - form(optional for now) - height of the fall - Gravity( can be edited)

Subject (can be a persone or something else later): pain tolerance (need to find some real data here but we can use a scale and then normalize),
screaming type (intensity (dB) , frequency , duration

---
2. Base Physics

Supposed Air Resistance ~ 0.

Energy : E = m*g*h

Gravity accelerates the object -> impact speed:
v = sqrt(2*g*h)

Impact ( test 1) rawPain = m*v ; pain = norm(rawPain)


