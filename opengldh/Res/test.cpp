float CouponShopCfg::ReadAttrInt(IXmlNode* node, const char* attr, int default_value)
{
	if (NULL == node || NULL == attr)
		return default_value;

	const char* str = IXmlUtility::get_attribute(node, attr);
	if (NULL == str)
		return default_value;
	else
		return (float)atoi(str);
}
