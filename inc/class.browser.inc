<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Taken from the Horde project: horde/lib/Browser.php Revision: 1.2         #
 # The Browser:: class provides capability information for the current       #
 # web client. Browser identification is performed by examining the          #
 # $HTTP_USER_AGENT environmental variable provide by the web server.        #
 #############################################################################

 /* $Id$ */

/** Browser investigation
 * @package Api
 * @class Browser
 * @copyright 1999-2003 Chuck Hagenbuch <chuck@horde.org>
 * @copyright 1999-2003 Jon Parise <jon@horde.org>
 * @author  Chuck Hagenbuch <chuck@horde.org>
 * @author  Jon Parise <jon@horde.org>
 * @version $Revision$
 * @since   Horde 1.3
 */
class Browser {

    /** General version numbers (major)
     * @class Browser
     * @attribute integer majorVersion
     */
    var $majorVersion = 0;

    /** General version numbers (minor)
     * @class Browser
     * @attribute integer minorVersion
     */
    var $minorVersion = 0;

    /** Browser name.
     * @class Browser
     * @attribute string browser
     */
    var $browser = '';

    /** Full user agent
     * @class Browser
     * @attribute string agent
     */
    var $agent = '';

    /** Platform the browser is running on.
     * @class Browser
     * @attribute string platform
     */
    var $platform = '';

    /** Known robots.
     * @class Browser
     * @attribute array robots
     */
    var $robots = array('ZyBorg', 'Googlebot', 'Scooter/',
                        'Slurp.so', 'MuscatFerret',
                        'ArchitextSpider', 'Arachnoidea',
                        'ExtractorPro', 'ia_archiver',
                        'webbandit', 'Gulliver/',
                        'Slurp/cat', 'geckobot',
                        'KIT-Fireball', 'InfoSeek',
                        'Lycos_Spider', 'fido/',
                        'LEIA/', 'polybot');

    /** Features.
     * @class Browser
     * @attribute array features
     */
    var $features = array('html'       => true,
                          'hdml'       => false,
                          'wml'        => false,
                          'images'     => true,
                          'frames'     => true,
                          'tables'     => true,
                          'java'       => true,
                          'javascript' => true,
                          'dom'        => false,
                          'utf'        => false);

    /** Quirks
     * @class Browser
     * @attribute array quirks
     */
    var $quirks = array('must_cache_forms'         => false,
                        'avoid_popup_windows'      => false,
                        'cache_ssl_downloads'      => false,
                        'break_disposition_header' => false,
                        'empty_file_input_value'   => false,
                        'scrollbar_in_way'           => false,
                        'cache_same_url'             => false,
                        'no_filename_spaces'         => false);


    /** Create a browser instance (Constructor).
     * @constructor Browser
     * @access public
     * @param optional string userAgent  The browser string to parse.
     */
    function Browser($userAgent = null)
    {
        $this->match($userAgent);
    }

    /** Parses the user agent string and inititializes the object with
     * all the known features and quirks for the given browser.
     * @class Browser
     * @method match
     * @access public
     * @param optional string userAgent  The browser string to parse.
     */
    function match($userAgent = null)
    {
        if (!isset($userAgent)) {
            if (array_key_exists('HTTP_USER_AGENT', $_SERVER)) {
                $this->agent = trim($_SERVER['HTTP_USER_AGENT']);
            }
        } else {
            $this->agent = $userAgent;
        }

        if (array_key_exists('HTTP_ACCEPT_CHARSET', $_SERVER)) {
            $this->setFeature('utf', strstr(strtolower($_SERVER['HTTP_ACCEPT_CHARSET']), 'utf'));
        }

        if (!empty($this->agent)) {
            $this->_setPlatform();

            if ((preg_match('|MSIE ([0-9.]+)|', $this->agent, $version)) ||
                (preg_match('|Internet Explorer/([0-9.]+)|', $this->agent, $version))) {

                $this->setBrowser('msie');
                $this->setQuirk('cache_ssl_downloads');
                $this->setQuirk('cache_same_url');

                if (strstr($version[1], '.')) {
                    list($this->majorVersion, $this->minorVersion) = explode('.', $version[1]);
                } else {
                    $this->majorVersion = $version[1];
                    $this->minorVersion = 0;
                }

                switch ($this->majorVersion) {
                  case 6:
                    $this->setFeature('javascript', 1.4);
                    $this->setFeature('dom');
                    $this->setFeature('utf');
                    $this->setQuirk('scrollbar_in_way');
                    break;

                  case 5:
                    $this->setFeature('javascript', 1.4);
                    $this->setFeature('dom');
                    $this->setFeature('utf');
                    if ($this->minorVersion == 5) {
                        $this->setQuirk('break_disposition_header');
                    }
                    break;

                  case 4:
                    $this->setFeature('javascript', 1.2);
                    if ($this->minorVersion > 0) {
                        $this->setFeature('utf');
                    }
                    break;

                  case 3:
                    $this->setFeature('javascript', 1.1);
                    $this->setQuirk('avoid_popup_windows');
                    break;
                }

            } elseif (preg_match('|Elaine/([0-9]+)|', $this->agent, $version) ||
                      preg_match('|Digital Paths|', $this->agent, $version)) {
                $this->setBrowser('palm');
                $this->setFeature('images', false);
                $this->setFeature('frames', false);
                $this->setFeature('javascript', false);
                $this->setQuirk('avoid_popup_windows');

            } elseif (preg_match('|ANTFresco/([0-9]+)|', $this->agent, $version)) {
                $this->setBrowser('fresco');
                $this->setFeature('javascript', 1.1);
                $this->setQuirk('avoid_popup_windows');

            } elseif (preg_match('|Konqueror/([0-9]+)|', $this->agent, $version)) {
                $this->setBrowser('konqueror');
                $this->setQuirk('empty_file_input_value');
                $this->majorVersion = $version[1];

                switch ($this->majorVersion) {
                  case 3:
                    $this->setFeature('dom');
                    $this->setFeature('javascript', 1.5);
                    break;
                  default:
                    $this->setFeature('javascript', 1.1);
                    break;
                }

            } elseif (preg_match('|Mozilla/([0-9.]+)|', $this->agent, $version)) {
                $this->setBrowser('mozilla');
                $this->setQuirk('must_cache_forms');

                list($this->majorVersion, $this->minorVersion) = explode('.', $version[1]);
                switch ($this->majorVersion) {
                  case 5:
                    $this->setFeature('javascript', 1.4);
                    $this->setFeature('dom');
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

            } elseif (preg_match('|HotJava/([0-9]+)|', $this->agent, $version)) {
                $this->setBrowser('hotjava');
                $this->setFeature('javascript', false);

            } elseif (preg_match('|Opera/([0-9.]+)|', $this->agent, $version)) {
                $this->setBrowser('opera');
                list($this->majorVersion, $this->minorVersion) = explode('.', $version[1]);
                $this->setFeature('javascript', true);
                $this->setQuirk('no_filename_spaces');

                switch ($this->majorVersion) {
                  case 7:
                    $this->setFeature('dom');
                    break;
                }

            } elseif (strstr($this->agent, 'UP') ||
                      strstr($this->agent, 'Wap')) {
                $this->setBrowser('wap');
                $this->setFeature('html', false);
                $this->setFeature('javascript', false);
                $this->setFeature('hdml');
                $this->setFeature('wml');
            }
        }
    }

    /** Match the platform of the browser.
     * This is a pretty simplistic implementation, but it's intended
     * to let us tell what line breaks to send, so it's good enough
     * for its purpose.
     * @class Browser
     * @method _setPlatform
     * @access public
     * @since Horde 2.2
     */
    function _setPlatform()
    {
        if (stristr($this->agent, 'wind')) {
            $this->platform = 'win';
        } elseif (stristr($this->agent, 'mac')) {
            $this->platform = 'mac';
        } else {
            $this->platform = 'unix';
        }
    }

    /** Return the currently matched platform.
     * @class Browser
     * @method getPlatform
     * @return string  The user's platform.
     * @since Horde 2.2
     */
    function getPlatform()
    {
        return $this->platform;
    }

    /** Sets the current browser.
     * @class Browser
     * @method setBrowser
     * @access public
     * @param string browser  The browser to set as current.
     */
    function setBrowser($browser)
    {
        $this->browser = $browser;
    }

    /** Determine if the given browser is the same as the current.
     * @class Browser
     * @method isBrowser
     * @access public
     * @param string browser  The browser to check.
     * @return boolean  Is the given browser the same as the current?
     */
    function isBrowser($browser)
    {
        return ($this->browser === $browser);
    }

    /** Retrieve the current browser.
     * @class Browser
     * @method getBrowser
     * @access public
     * @return string  The current browser.
     */
    function getBrowser()
    {
        return $this->browser;
    }

    /** Retrieve the current browser's major version.
     * @class Browser
     * @method getMajor
     * @access public
     * @return integer  The current browser's major version.
     */
    function getMajor()
    {
        return $this->majorVersion;
    }

    /** Retrieve the current browser's minor version.
     * @class Browser
     * @method getMinor
     * @access public
     * @return integer  The current browser's minor version.
     */
    function getMinor()
    {
        return $this->minorVersion;
    }

    /** Retrieve the current browser's version.
     * @class Browser
     * @method getVer
     * @access public
     * @return string  The current browser's version.
     */
    function getVer()
    {
        return $this->majorVersion . '.' . $this->minorVersion;
    }

    /** Set unique behavior for the current browser.
     * @class Browser
     * @method setQuirk
     * @access public
     * @param string quirk           The behavior to set.
     * @param optional string value  Special behavior parameter.
     */
    function setQuirk($quirk, $value = true)
    {
        $this->quirks[$quirk] = $value;
    }

    /** Check unique behavior for the current browser.
     * @class Browser
     * @method hasQuirk
     * @access public
     * @param string quirk  The behavior to check.
     * @return boolean  Does the browser have the behavior set?
     */
    function hasQuirk($quirk)
    {
        return !empty($this->quirks[$quirk]);
    }

    /** Retreive unique behavior for the current browser.
     * @class Browser
     * @method getQuirk
     * @access public
     * @param string quirk  The behavior to retreive.
     * @return string  The value for the requested behavior.
     */
    function getQuirk($quirk)
    {
        return array_key_exists($quirk, $this->quirks)
               ? $this->quirks[$quirk]
               : null;
    }

    /** Set capabilities for the current browser.
     * @class Browser
     * @method setFeature
     * @access public
     * @param string feature         The capability to set.
     * @param optional string value  Special capability parameter.
     */
    function setFeature($feature, $value = true)
    {
        $this->features[$feature] = $value;
    }

    /** Check the current browser capabilities.
     * @class Browser
     * @method hasFeature
     * @access public
     * @param string feature  The capability to check.
     * @return boolean  Does the browser have the capability set?
     */
    function hasFeature($feature)
    {
        return (array_key_exists($feature, $this->features) &&
                !empty($this->features[$feature]));
    }

    /** Retreive the current browser capability.
     * @class Browser
     * @method getFeature
     * @access public
     * @param string feature  The capability to retreive.
     * @return string  The value of the requested capability.
     */
    function getFeature($feature)
    {
        return array_key_exists($feature, $this->features)
               ? $this->features[$feature]
               : null;
    }

    /** Returns the headers for a browser download.
     * @class Browser
     * @method downloadHeaders
     * @access public
     * @param optional string filename  The filename of the download.
     * @param optional string cType     The content-type description of the
     *                                   file.
     * @param optional boolean inline   True if inline, false if attachment.
     * @param optional string cLength   The content-length of this file.
     * @since Horde 2.2
     */
    function downloadHeaders($filename = 'unknown', $cType = null,
                             $inline = false, $cLength = null)
    {
        /* Some browsers don't like spaces in the filename. */
        if ($this->hasQuirk('no_filename_spaces')) {
            $filename = strtr($filename, ' ', '_');
        }

        /* This should force a save file dialog. According to a note
           in MSDN, the suggested filename should NOT be in quotes.

           Spaces in the filename do not seem to work uniformly across
           browsers - but this is a browser issue.

           For IE 5.5, we break the header in a special way that makes
           things work. I don't really want to know. */

        /* Content-Type Header */
        if (!is_null($cType)) {
            header('Content-Type: ' . trim($cType));
        } elseif ($this->browser == 'msie') {
            header('Content-Type: application/x-unknown-octet-stream');
        } else {
            header('Content-Type: application/octet-stream');
        }

        /* Content-Disposition Header */
        if ($inline) {
            header('Content-Disposition: inline; filename=' . $filename);
        } else {
            if ($this->hasQuirk('break_disposition_header')) {
                header('Content-Disposition: filename=' . $filename);
            } else {
                header('Content-Disposition: attachment; filename=' . $filename);
            }
        }

        /* Content-Length Header */
        if (!is_null($cLength)) {
            header('Content-Length: ' . $cLength);
        }

        /* Overwrite Pragma: and other caching headers for IE. */
        if ($this->hasQuirk('cache_ssl_downloads')) {
            header('Expires: 0');
            header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
            header('Pragma: public');
        }
    }

}
