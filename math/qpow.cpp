ll qpow(ll a,ll n)
{
	ll ans=1;
	while(n)
	{
		if(n & 1)
			ans = (ans * a) % mod;
		a = (a * a) % mod;
		n >>= 1;
	}
	return ans;
}