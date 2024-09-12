EffectAreaBuff = EffectAreaBuff or {}

function EffectAreaBuff:OnMouseMove()
  return true
end

function EffectAreaBuff:OnMouseOver(hover)
  local index = GetIndexFromString(self:GetParent().name)
  self.context:OnEffectAreaIconOver(index, true, hover)
end

EffectAreaDebuff = EffectAreaDebuff or {}

function EffectAreaDebuff:OnMouseMove()
  return true
end

function EffectAreaDebuff:OnMouseOver(hover)
  local index = GetIndexFromString(self:GetParent().name)
  self.context:OnEffectAreaIconOver(index, false, hover)
end

