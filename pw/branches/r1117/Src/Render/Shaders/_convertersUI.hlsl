#define UNDEFINED 0

float3 RGB2HSV( float3 color )
{
  // RGB are each on [0, 1]. S and V are returned on [0, 1] and H is
  // returned on [0, 1]. Exception: H is returned UNDEFINED if S==0.
  float R = color.x;
  float G = color.y;
  float B = color.z;
  float v, x, f;
  int i;
  //x = min(R, G, B);
  x = min(R, G);
  x = min(x, B);
  //v = max(R, G, B);
  v = max(R, G);
  v = max(v, B);
  if(v == x) 
     return float3(UNDEFINED, 0, v);
  else
  {   
     if(R == x) { f = G - B; } else if(G == x) { f = B - R; } else { f = R - G; }
     if(R == x) { i = 3; } else if(G == x) { i = 5; } else { i = 1; }
     return float3(((i - f /(v - x))/6), (v - x)/v, v);
  }  
}

float3 HSV2RGB( float3 hsv_color )
{
  // H is given on [0, 1] or UNDEFINED. S and V are given on [0, 1].
  // RGB are each returned on [0, 1].
  float h = hsv_color.x * 6; 
  float s = hsv_color.y; 
  float v = hsv_color.z;
  float m, n, f;
  int i;
  if (h == 0) { h=0.01; }
  if(h == UNDEFINED) 
  { 
     return float3(v, v, v); 
  }
  else
  {
     i = floor(h);
     f = h - i;
     if((i % 2)==0) { f = 1 - f; } // if i is even
     m = v * (1 - s);
     n = v * (1 - s * f);

     if(i==6) { return float3(v, n, m); }
     else if(i==0) { return float3(v, n, m); }
     else if(i==1) { return float3(n, v, m); }
     else if(i==2) { return float3(m, v, n); }
     else if(i==3) { return float3(m, n, v); }
     else if(i==4) { return float3(n, m, v); }
     else if(i==5) { return float3(v, m, n); }
     else return float3(0, 0, 0);   
  }   
}
