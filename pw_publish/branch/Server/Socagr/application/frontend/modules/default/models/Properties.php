<?php
class Properties
{
    protected $_db;

    public function __construct()
    {
        $this->_db = Mongosa::getInstance();
    }

    public function add($auid,$secondAuid,$propertyName,$propertyValue)
    {
        $propertyName = strtolower($propertyName);
        $collection = $this->_db->properties;
        $result = $collection->update(array('_id' => $propertyName), array('_id' => $propertyName),array('upsert' => true)); // 'safe' or 'w' => true by default
        if($result['ok'] == 1)
        {
            $collection = $this->_db->user_properties;
            $id = (int)$auid > (int)$secondAuid ? $auid.'_'.$secondAuid : $secondAuid.'_'.$auid;
            $id = $id.'_'.$propertyName;
            $result = $collection->update(array('_id' => $id), array('_id' => $id,'value' => $propertyValue,'name' => $propertyName, 'auid' => (int)$auid, 'e_auid' => (int)$secondAuid),array('upsert' => true));
            if($result['ok'] == 1)
            {
                return true;
            }
            else
            {
                throw new Exception($result['err']);
            }
        }
        else
        {
            throw new Exception($result['err']);
        }
    }

    public function getProperty($propertyName)
    {
        $propertyName = strtolower($propertyName);
        $collection = $this->_db->properties;
        return $collection->findOne(array('_id' => $propertyName),array());
    }

    public function getUsersProperty($auid,$secondAuid,$propertyName)
    {
        $propertyName = strtolower($propertyName);
        $collection = $this->_db->user_properties;
        $id = (int)$auid > (int)$secondAuid ? $auid.'_'.$secondAuid : $secondAuid.'_'.$auid;
        $id = $id.'_'.$propertyName;
        return $collection->findOne(array('_id' => $id),array());
    }

    public function getUserEdgeProperties($auid)
    {
        $collection = $this->_db->user_properties;
        return $collection->find(array('$or' => array( array('auid' => (int)$auid), array('e_auid' => (int)$auid))),array());
    }

    public function removeUsersProperty($auid,$secondAuid,$propertyName)
    {
        $propertyName = strtolower($propertyName);
        $collection = $this->_db->user_properties;
        $id = (int)$auid > (int)$secondAuid ? $auid.'_'.$secondAuid : $secondAuid.'_'.$auid;
        $id = $id.'_'.$propertyName;
        return $collection->remove(array('_id' => $id));
    }
}
?>