<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Taken from the Horde project: horde/lib/Browser.php Revision: 1.2         *
 * The Browser:: class provides capability information for the current       *
 * web client. Browser identification is performed by examining the          *
 * $HTTP_USER_AGENT environmental variable provide by the web server.        *
 \***************************************************************************/

 /* $Id$ */

class Browser {
    
    /**
     * General version numbers
     */
    var $majorVersion = 0;
    var $minorVersion = 0;
    
    /**
     * Browser name
     */
    var $browser = '';
    
    /**
     * Full user agent
     */
    var $agent = '';
    
    /**
     * Features
     */
    var $features = array('html'       => true,
                          'hdml'       => false,
                          'wml'        => false,
                          'images'     => true,
                          'frames'     => true,
                          'tables'     => true,
                          'java'       => true,
                          'javascript' => true);
    
    /**
     * Quirks
     */
    var $quirks = array('must_cache_forms'         => false,
                        'avoid_popup_windows'      => false,
                        'cache_ssl_downloads'      => false,
                        'break_disposition_header' => false);
    
    
    /**
     * Create a browser instance
     */
    function Browser($userAgent = null)
    {
        $this->match($userAgent);
    }
    
    /**
     * Parses the user agent string and inititializes the object with
     * all the known features and quirks for the given browser.
     *
     * @param string $userAgent (optional) The browser string to parse
     */
    function match($userAgent = null)
    {
        if (!isset($userAgent)) {
            if (isset($GLOBALS['HTTP_SERVER_VARS']['HTTP_USER_AGENT'])) {
                $this->agent = trim($GLOBALS['HTTP_SERVER_VARS']['HTTP_USER_AGENT']);
            }
        } else {
            $this->agent = $userAgent;
        }
        
        if (!empty($this->agent)) {
            if ((preg_match('|MSIE ([0-9.]+)|', $this->agent, $version)) ||
                (preg_match('|Internet Explorer/([0-9.]+)|', $this->agent, $version))) {
                
                $this->setBrowser('msie');
                $this->setQuirk('cache_ssl_downloads');
                
                list($this->majorVersion, $this->minorVersion) = explode('.', $version[1]);
                switch($this->majorVersion) {
                case 6:
                    $this->setFeature('javascript', 1.4);
                    break;
                case 5:
                    $this->setFeature('javascript', 1.4);
                    if ($this->minorVersion == 5) {
                        $this->setQuirk('break_disposition_header');
                    }
                    break;
                case 4:
                    $this->setFeature('javascript', 1.2);
                    break;
                case 3:
                    $this->setFeature('javascript', 1.1);
                    $this->setQuirk('avoid_popup_windows');
                    break;
                }
                
            } elseif (preg_match('|ANTFresco/([0-9]+)|', $this->agent, $version)) {
                $this->setBrowser('fresco');
                $this->setFeature('javascript', 1.1);
                $this->setQuirk('avoid_popup_windows');
                
            } elseif (preg_match('|Mozilla/([0-9.]+)|', $this->agent, $version)) {
                $this->setBrowser('netscape');
                $this->setQuirk('must_cache_forms');
                
                list($this->majorVersion, $this->minorVersion) = explode('.', $version[1]);
                switch($this->majorVersion) {
                case 5:
                    $this->setFeature('javascript', 1.4);
                    break;
                case 4:
                    $this->setFeature('javascript', 1.3);
                    break;
                case 3:
                default:
                    $this->setFeature('javascript', 1);
                    break;
                }
                
            } elseif (preg_match('|Lynx/([0-9]+)|', $this->agent, $version)) {
                $this->setBrowser('lynx');
                $this->setFeature('images', false);
                $this->setFeature('frames', false);
                $this->setFeature('javascript', false);
                $this->setQuirk('avoid_popup_windows');
                
            } elseif (preg_match('|Links \(([0-9]+)|', $this->agent, $version)) {
                $this->setBrowser('links');
                $this->setFeature('images', false);
                $this->setFeature('frames', false);
                $this->setFeature('javascript', false);
                $this->setQuirk('avoid_popup_windows');
                
            } elseif (preg_match('|Konqueror/([0-9]+)|', $this->agent, $version)) {
                $this->setBrowser('konqueror');
                $this->setFeature('javascript', false);
                
            } elseif (preg_match('|HotJava/([0-9]+)|', $this->agent, $version)) {
                $this->setBrowser('hotjava');
                $this->setFeature('javascript', false);
                
            } elseif (preg_match('|Opera/([0-9.]+)|', $this->agent, $version)) {
                $this->setBrowser('opera');
                list($this->majorVersion, $this->minorVersion) = explode('.', $version[1]);
                $this->setFeature('javascript', false);
                
            } elseif (preg_match('|UP|', $this->agent, $version) ||
                      preg_match('|Wap|', $this->agent, $version)) {
                $this->setBrowser('wap');
                $this->setFeature('html', false);
                $this->setFeature('hdml');
                $this->setFeature('wml');
            }
        }
    }
    
    
    /**
     * Sets the current browser.
     *
     * @param string $browser The browser to set as current
     */
    function setBrowser($browser)
    {
        $this->browser = $browser;
    }
    
    /**
     * Determine if the given browser is the same as the current.
     *
     * @param string $browser The browser to check
     *
     * @return boolean Is the given browser the same as the current?
     */
    function isBrowser($browser)
    {
        return ($this->browser === $browser);
    }
    
    /**
     * Retreive the current browser.
     *
     * @return boolean Current browser
     */
    function getBrowser()
    {
        return $this->browser;
    }
    
    /**
     * Retreive the current browsers major version.
     *
     * @return boolean Current browser
     */
    function getMajor()
    {
        return $this->majorVersion;
    }
    
    /**
     * Retreive the current browsers minor version.
     *
     * @return boolean Current browser
     */
    function getMinor()
    {
        return $this->minorVersion;
    }
    
    /**
     * Retreive the current browsers version.
     *
     * @return boolean Current browser
     */
    function getVer()
    {
        return $this->majorVersion . "." . $this->minorVersion;
    }
    
    /**
     * Set unique behavior for the current browser.
     *
     * @param string $quirk The behavior to set
     * @param string $value (optional) Special behavior parameter
     */
    function setQuirk($quirk, $value = true)
    {
        $this->quirks[$quirk] = $value;
    }
    
    /**
     * Check unique behavior for the current browser
     *
     * @param string $quirk The behavior to check
     *
     * @return boolean Does the browser have the behavior set?
     */
    function hasQuirk($quirk)
    {
        return !empty($this->quirks[$quirk]);
    }
    
    /**
     * Retreive unique behavior for the current browser
     *
     * @param string $quirk The behavior to retreive
     *
     * @return string The value for the requested behavior
     */
    function getQuirk($quirk)
    {
        return isset($this->quirks[$quirk]) ? $this->quirks[$quirk] : null;
    }
    
    /**
     * Set capabilities for the current browser.
     *
     * @param string $feature The capability to set
     * @param string $value (optional) Special capability parameter
     */
    function setFeature($feature, $value = true)
    {
        $this->features[$feature] = $value;
    }
    
    /**
     * Check the current browser capabilities.
     *
     * @param string $feature The capability to check
     *
     * @return boolean Does the browser have the capability set?
     */
    function hasFeature($feature)
    {
        return !empty($this->features[$feature]);
    }
    
    /**
     * Retreive the current browser capability.
     *
     * @param string $feature The capability to retreive
     *
     * @return string The value of the requested capability
     */
    function getFeature($feature)
    {
        return isset($this->features[$feature]) ? $this->features[$feature] : null;
    }
    
}
?>
